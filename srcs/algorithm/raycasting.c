/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:46:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/12 02:55:16 by mpeharpr         ###   ########.fr       */
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

/* If the player is not on an intersection point atm, search for the next intersection point
depending on his ang in order to allow us to add step_x and step_y later */
static void    move_to_next_point(t_ray *ray)
{
    double  next_x;
    double  next_y;

    // TODO: Scan on the other axis everytime and get the lowest distance
    if ((ray->ang >= 0 && ray->ang <= 45) || ray->ang >= 315)
    {
        next_x = ray->cur_x + (CUBES_SIZE - (fmod(ray->cur_x, CUBES_SIZE)));
        next_y = ray->cur_y - ((next_x - ray->cur_x) * tan(ray->rad));
    }
    else if (ray->ang > 45 && ray->ang <= 135)
    {
        next_y = ray->cur_y - (CUBES_SIZE - (fmod(ray->cur_y, CUBES_SIZE)));
        next_x = ray->cur_x - ((next_y - ray->cur_y) / tan(ray->rad));
    }
    else if (ray->ang > 135 && ray->ang <= 225)
    {
        next_x = ray->cur_x - (CUBES_SIZE - (fmod(ray->cur_x, CUBES_SIZE)));
        next_y = ray->cur_y - ((next_x - ray->cur_x) * tan(ray->rad));
    }
    else
    {
        next_y = ray->cur_y + (CUBES_SIZE - (fmod(ray->cur_y, CUBES_SIZE)));
        next_x = ray->cur_x - ((next_y - ray->cur_y) / tan(ray->rad));
    }

    ray->cur_x = (next_x);
    ray->cur_y = (next_y);
}

/* Transform the position we got into a map position depending on the angle */
void    calculate_map_pos(t_ray *ray)
{
    int pos_x;
    int pos_y;

    /* This is the top-left position on the map */
    pos_x = (int)(ray->cur_x / CUBES_SIZE);
    pos_y = (int)(ray->cur_y / CUBES_SIZE);
    
    /* If the ray is going up, take the case above instead of the one below */
    if (ray->ang > 0 && ray->ang < 180)
        pos_y--;

    /* If the ray is going left, take the case on the left instead of the one on the right */
    if (ray->ang > 90 && ray->ang < 270)
        pos_x--;

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
    
    /* Initialize our angles and shit */
    ray.ang = fmod(ray_ang, 360);
    if (ray.ang < 0)
        ray.ang += 360;
    ray.rad = (ray_ang * M_PI) / 180;
    calculate_map_pos(&ray);

    /* Before doing anything, search for the first intersection point */
    while (42)
    {
        ray.prev_x = ray.cur_x;
        ray.prev_y = ray.cur_y;
        move_to_next_point(&ray);
        calculate_map_pos(&ray);
        if (ray.map[ray.cur_map_y][ray.cur_map_x] == '1')
        {
            dist = calc_dist(ray.start_x, ray.start_y, ray.cur_x, ray.cur_y);
            break ;
        }
    }

    return (dist);
}
