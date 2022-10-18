/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:46:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 11:12:20 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Transform the position we got into a map position depending on the angle */
static void	calc_map(t_ray *ray, double x, double y, double is_vert)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)(ceil_double(x / CUBES_SIZE));
	pos_y = (int)(ceil_double(y / CUBES_SIZE));
	if (is_vert && ray->ang > 90 && ray->ang < 270)
		pos_x--;
	else if (!is_vert && ray->ang > 0 && ray->ang < 180)
		pos_y--;
	if (pos_x < 0 || pos_x > ray->size_x || pos_y < 0 || pos_y > ray->size_y)
		free_ray_when_problem(ray, ERR_RAY);
	ray->cur_map_x = pos_x;
	ray->cur_map_y = pos_y;
}

/* Initialize the ray structure correctly before doing anything */
static void	init_raycast(t_game *game, t_ray *ray, double ray_ang, int *i)
{
	*i = 0;
	ray->map = game->infomap->map;
	ray->start_x = game->ply->pos_x;
	ray->start_y = game->ply->pos_y;
	ray->size_x = game->infomap->size_x;
	ray->size_y = game->infomap->size_y;
	ray->found_vert = NULL;
	ray->found_horiz = NULL;
	ray->order = NULL;
	ray->ang = fmod(ray_ang, 360);
	if (ray->ang < 0)
		ray->ang += 360;
	ray->rad = (ray_ang * M_PI) / 180;
	ray->game = game;
}

/* Get the wall orientation depending on the player position, the ray
final position and the ray angle */
static void	calc_wall_orientation(t_ray *ray, t_raysult *res, int i)
{
	if (ray->order[i][2] == 0)
	{
		res->offset = ray->order[i][0] - ray->cur_map_x * 64;
		if (ray->order[i][1] - ray->start_y < 0)
			res->wall_orientation = 'N';
		else
			res->wall_orientation = 'S';
	}
	else
	{
		res->offset = ray->order[i][1] - ray->cur_map_y * 64;
		if (ray->order[i][0] - ray->start_x < 0)
			res->wall_orientation = 'W';
		else
			res->wall_orientation = 'E';
	}
	res->offset = fmod(res->offset, 64);
}

/* Send a ray from the player position to a specific angle of the map
and return the distance of the first obstacle found on the way and
the offset (modulo 64) for later wall texturing */
void	send_raycast(t_game *game, double ray_ang, t_raysult *res)
{
	t_ray	ray;
	int		i;

	init_raycast(game, &ray, ray_ang, &i);
	alloc_ray_intersections(&ray);
	find_vert_inter(&ray);
	find_horiz_inter(&ray);
	create_inter_array(&ray);
	while (i < ray.size_x + ray.size_y)
	{
		if (ray.order[i][0] != -1.0 && ray.order[i][1] != -1.0)
		{
			calc_map(&ray, ray.order[i][0], ray.order[i][1], ray.order[i][2]);
			if (ray.map[ray.cur_map_y][ray.cur_map_x] == '1')
			{
				calc_wall_orientation(&ray, res, i);
				res->dist = calc_dist(ray.start_x, ray.start_y, \
				ray.order[i][0], ray.order[i][1]) * cos((ray.ang - \
				game->ply->ang_y) * M_PI / 180);
				break ;
			}
		}
		i++;
	}
	free_ray_intersections(&ray);
}
