/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:46:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 03:14:54 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Calculate the distance between 2 points */
double	calc_dist(double x1, double y1, double x2, double y2)
{
	double		dist;

	dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return	(dist);
}

/* Find every intersection on vertical lines (moving left/right on the X axis)
and put everything in an array */
static void	find_vert_inter(t_ray *ray)
{
	double		x;
	double		y;
	double		dist;
	int			idx;

	if (ray->ang == 90 || ray->ang == 270)
		return ;
	idx = 0;
	x = ray->cur_x;
	while (x < ray->size_x * CUBES_SIZE && x > 0)
    {
        dist = fmod(x, CUBES_SIZE);
        if (ray->ang > 90 && ray->ang < 270)
        {
            if (dist == 0)
                dist = CUBES_SIZE;   
            x -= dist;
        }
        else
            x += CUBES_SIZE - dist;
        x = ceil_double(x);
        
        if (ray->ang == 0 || ray->ang == 180)
            y = ray->cur_y;
        else
            y = ceil_double(ray->cur_y - (x - ray->cur_x) * tan(ray->rad));
        if (y < 0 || y > ray->size_y * CUBES_SIZE)
            break ;

        ray->found_vert[idx][0] = x;
        ray->found_vert[idx][1] = y;
        idx++;
    }
}

/* Find every intersection on horizontal lines (moving up/down on the Y axis)
and put everything in an array */
static void find_horiz_inter(t_ray *ray)
{
    double  x;
    double  y;
    double  dist;
    int     idx;

    if (ray->ang == 0 || ray->ang == 180)
        return ;
    idx = 0;
    y = ray->cur_y;
    while (y < ray->size_y * CUBES_SIZE && y > 0)
    {
        dist = fmod(y, CUBES_SIZE);
        if (ray->ang >= 0 && ray->ang <= 180)
        {
            if (dist == 0)
                dist = CUBES_SIZE;   
            y -= dist;
        }
        else
            y += CUBES_SIZE - dist;
        y = ceil_double(y);
        
        if (ray->ang == 90 || ray->ang == 270)
            x = ray->cur_x;
        else
            x = ceil_double(ray->cur_x - (y - ray->cur_y) / tan(ray->rad));
        if (x < 0 || x > ray->size_x * CUBES_SIZE)
            break ;

        ray->found_horiz[idx][0] = x;
        ray->found_horiz[idx][1] = y;
        idx++;
    }
}

/* Transform the position we got into a map position depending on the angle */
void    calculate_map_pos(t_ray *ray, double x, double y, double is_vert)
{
    int pos_x;
    int pos_y;

    /* This is the top-left position on the map */
    pos_x = (int)(ceil_double(x / CUBES_SIZE));
    pos_y = (int)(ceil_double(y / CUBES_SIZE));

    if (is_vert && ray->ang > 90 && ray->ang < 270)
        pos_x--;
    else if (!is_vert && ray->ang > 0 && ray->ang < 180)
        pos_y--;

    if (pos_x < 0 || pos_x > ray->size_x || pos_y < 0 || pos_y > ray->size_y)
    {
        printf("The ray has been out of the map, unexpected problem, aborting!\n");
        exit(0); // TODO: Change this
    }

    ray->cur_map_x = pos_x;
    ray->cur_map_y = pos_y;
}

/* Create a new array containing all intersections point (from our both arrays) order by distance */
static void create_inter_array(t_ray *ray)
{
    int i;
    int j;
    int idx;

    i = 0;
    j = 0;
    idx = 0;
    while (i < ray->size_x || j < ray->size_y)
    {
        if (i < ray->size_x && j < ray->size_y && ray->found_vert[i][0] != -1 && ray->found_horiz[j][0] != -1)
        {
            /* If the vertical intersection is closer than the horizontal one */
            if (calc_dist(ray->cur_x, ray->cur_y, ray->found_vert[i][0], ray->found_vert[i][1]) < calc_dist(ray->cur_x, ray->cur_y, ray->found_horiz[j][0], ray->found_horiz[j][1]))
            {
                ray->found_order[idx][0] = ray->found_vert[i][0];
                ray->found_order[idx][1] = ray->found_vert[i][1];
                ray->found_order[idx][2] = 1;
                i++;
            }
            else
            {
                ray->found_order[idx][0] = ray->found_horiz[j][0];
                ray->found_order[idx][1] = ray->found_horiz[j][1];
                ray->found_order[idx][2] = 0;
                j++;
            }
        }
        else if (i < ray->size_x && ray->found_vert[i][0] != -1)
        {
            ray->found_order[idx][0] = ray->found_vert[i][0];
            ray->found_order[idx][1] = ray->found_vert[i][1];
            ray->found_order[idx][2] = 1;
            i++;
        }
        else if (j < ray->size_y && ray->found_horiz[j][0] != -1)
        {
            ray->found_order[idx][0] = ray->found_horiz[j][0];
            ray->found_order[idx][1] = ray->found_horiz[j][1];
            ray->found_order[idx][2] = 0;
            j++;
        }
        else
            break ;
        idx++;
    }
}

/* Send a ray from the player position to a specific angle of the map
and return the distance of the first obstacle found on the way and
the offset (modulo 64) for later wall texturing */
void    send_raycast(t_game *game, double ray_ang, t_raysult *res)
{
    t_ray       ray;
    double      dist;
    double      offset;

    dist = 0;
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

    /* Allocate all arrays */
    ray.found_vert = malloc(sizeof(double *) * ray.size_x);
    if (!ray.found_vert)
        exit(0); // TODO: Change this
    ray.found_horiz = malloc(sizeof(double *) * ray.size_y);
    if (!ray.found_horiz)
        exit(0); // TODO: Change this
    ray.found_order = malloc(sizeof(double *) * (ray.size_x + ray.size_y));
    if (!ray.found_order)
        exit(0); // TODO: Change this

    /* Allocate all subarrays for each array */
    for (int i = 0; i < ray.size_x; i++)
    {
        ray.found_vert[i] = malloc(sizeof(double) * 2);
        if (!ray.found_vert[i])
            exit(0); // TODO: Change this
        ray.found_vert[i][0] = -1.0;
        ray.found_vert[i][1] = -1.0;
    }
    for (int i = 0; i < ray.size_y; i++)
    {
        ray.found_horiz[i] = malloc(sizeof(double) * 2);
        if (!ray.found_horiz[i])
            exit(0); // TODO: Change this
        ray.found_horiz[i][0] = -1.0;
        ray.found_horiz[i][1] = -1.0;
    }
    for (int i = 0; i < ray.size_x + ray.size_y; i++)
    {
        ray.found_order[i] = malloc(sizeof(double) * 3);
        if (!ray.found_order[i])
            exit(0); // TODO: Change this
        ray.found_order[i][0] = -1.0;
        ray.found_order[i][1] = -1.0;
        ray.found_order[i][2] = 0.0; // 0 for horizontal, 1 for vertical
    }

    /* Send rays */
    find_vert_inter(&ray);
    find_horiz_inter(&ray);
    create_inter_array(&ray);

    /* Find the first intersection that is next to a wall */
    for (int i = 0; i < ray.size_x + ray.size_y; i++)
    {
        if (ray.found_order[i][0] != -1.0 && ray.found_order[i][1] != -1.0)
        {
            calculate_map_pos(&ray, ray.found_order[i][0], ray.found_order[i][1], ray.found_order[i][2]);                
            if (ray.map[ray.cur_map_y][ray.cur_map_x] == '1')
            {
                if (ray.found_order[i][2] == 0) // horizontal intersection
                    offset = ray.found_order[i][0] - ray.cur_map_x * 64;
                else // vertical intersection
                    offset = ray.found_order[i][1] - ray.cur_map_y * 64;
                offset = fmod(offset, 64);
                dist = calc_dist(ray.start_x, ray.start_y, ray.found_order[i][0], ray.found_order[i][1]);
                break;
            }
        }
    }
    
    /* Free the arrays */
    for (int i = 0; i < ray.size_x; i++)
        free(ray.found_vert[i]);
    free(ray.found_vert);
    for (int i = 0; i < ray.size_y; i++)
        free(ray.found_horiz[i]);
    free(ray.found_horiz);
    for (int i = 0; i < ray.size_x + ray.size_y; i++)
        free(ray.found_order[i]);
    free(ray.found_order);

    res->dist = dist * cos((ray.ang - game->player->ang_y) * M_PI / 180);
    res->offset = offset;
}
