/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:46:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/13 00:52:21 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Calculate the distance between 2 points */
double  calc_dist(double x1, double y1, double x2, double y2)
{
    double  dist;

    dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return (dist);
}


/* Find the next intersection point on every vertical line */
static void find_next_vertical_point(t_ray *ray)
{
    double  delta_y;
    double  next_y;
    double  delta_x;
    double  next_x;

    if (ray->ang == 0 || ray->ang == 180)
    {
        ray->vertical_found_x = ray->cur_x;
        ray->vertical_found_y = ray->cur_y;
        return ;
    }

    delta_y = (CUBES_SIZE - (fmod(ray->cur_y, CUBES_SIZE)));
    if (ray->ang >= 0 && ray->ang <= 180)
        next_y = ray->cur_y - delta_y;
    else
        next_y = ray->cur_y + delta_y;

    if (ray->ang == 0 || ray->ang == 180)
        delta_x = 0;
    else
        delta_x = ((next_y - ray->cur_y) / tan(ray->rad));
    next_x = ray->cur_x - delta_x;

    ray->vertical_found_x = next_x;
    ray->vertical_found_y = next_y;
}

/* Find the next intersection point on every horizontal line */
static void find_next_horizontal_point(t_ray *ray)
{
    double  delta_x;
    double  next_x;
    double  delta_y;
    double  next_y;

    if (ray->ang == 90 || ray->ang == 270)
    {
        ray->horizontal_found_x = ray->cur_x;
        ray->horizontal_found_y = ray->cur_y;
        return ;
    }
    
    delta_x = (CUBES_SIZE - (fmod(ray->cur_x, CUBES_SIZE)));
    if (ray->ang >= 90 && ray->ang <= 270)
        next_x = ray->cur_x - delta_x;
    else
        next_x = ray->cur_x + delta_x;

    if (ray->ang == 0 || ray->ang == 180)
        delta_y = 0;
    else
        delta_y = ((next_x - ray->cur_x) / tan(ray->rad));
    next_y = ray->cur_y - delta_y;

    ray->horizontal_found_x = next_x;
    ray->horizontal_found_y = next_y;
}

/* Transform the position we got into a map position depending on the angle */
void    calculate_map_pos(t_ray *ray)
{
    int pos_x;
    int pos_y;

    /* This is the top-left position on the map */
    pos_x = (int)ceil_double(ray->cur_x / CUBES_SIZE);
    pos_y = (int)ceil_double(ray->cur_y / CUBES_SIZE);
    
    /* If the ray is going up, take the case above instead of the one below */
    if (ray->ang > 0 && ray->ang < 180)
        pos_y--;

    /* If the ray is going left, take the case on the left instead of the one on the right */
    if (ray->ang > 90 && ray->ang < 270)
        pos_x--;

    if (pos_x < 0 || pos_x > ray->size_x || pos_y < 0 || pos_y > ray->size_y)
    {
        printf("The ray has been out of the map, unexpected problem, aborting!\n");
        exit(0); // TODO: Change this
    }

    ray->cur_map_x = pos_x;
    ray->cur_map_y = pos_y;
}

/* Send a ray from the player position to a specific angle of the map
and return the distance of the first obstacle found on the way */
double  send_raycast(t_game *game, double ray_ang)
{
    t_ray       ray;
    double      dist;

    ray.map = game->infomap->map;
    ray.start_x = game->player->pos_x;
    ray.start_y = game->player->pos_y;
    ray.cur_x = ray.start_x;
    ray.cur_y = ray.start_y;
    ray.size_x = game->infomap->size_x;
    ray.size_y = game->infomap->size_y;

    /* Initialize our angles and shit */
    ray.ang = fmod(ray_ang, 360);
    if (ray.ang < 0)
        ray.ang += 360;
    ray.rad = (ray_ang * M_PI) / 180;
    calculate_map_pos(&ray);

    /* Send rays */
    while (42)
    {
        find_next_vertical_point(&ray);
        find_next_horizontal_point(&ray);

        int is_vertical_invalid = (ray.vertical_found_x == ray.cur_x && ray.vertical_found_y == ray.cur_y);
        int is_horizontal_invalid = (ray.horizontal_found_x == ray.cur_x && ray.horizontal_found_y == ray.cur_y);
        int vertical_dist;
        int horizontal_dist;

        if (is_vertical_invalid && is_horizontal_invalid)
        {
            printf("Unable to found any good ray!\n");
            break ;
        }

        if (is_vertical_invalid)
            vertical_dist = INT_MAX;
        else
            vertical_dist = calc_dist(ray.cur_x, ray.cur_y, ray.vertical_found_x, ray.vertical_found_y);

        if (is_horizontal_invalid)
            horizontal_dist = INT_MAX;
        else
            horizontal_dist = calc_dist(ray.cur_x, ray.cur_y, ray.horizontal_found_x, ray.horizontal_found_y);

        if (vertical_dist < horizontal_dist)
        {
            ray.cur_x = ray.vertical_found_x;
            ray.cur_y = ray.vertical_found_y;
        }
        else
        {
            ray.cur_x = ray.horizontal_found_x;
            ray.cur_y = ray.horizontal_found_y;
        }

        ray.cur_x = ceil_double(ray.cur_x);
        ray.cur_y = ceil_double(ray.cur_y);

        calculate_map_pos(&ray);
        printf("Ray sent to %d %d detected by %s\n", ray.cur_map_x, ray.cur_map_y, (vertical_dist < horizontal_dist) ? "vertical" : "horizontal");

        if (ray.map[ray.cur_map_y][ray.cur_map_x] == '1')
        {
            dist = calc_dist(ray.start_x, ray.start_y, ray.cur_x, ray.cur_y);
            break ;
        }
    }

    return (dist);
}
