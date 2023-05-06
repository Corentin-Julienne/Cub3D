/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:46:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 10:01:55 by mpeharpr         ###   ########.fr       */
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

/* Called for every ray to check and break if the ray is invalid */
static int	is_invalid_ray(t_game *game, t_ray *ray, t_raysult *res)
{
	if (ray->cur_map_y >= game->infomap->size_y || ray->cur_map_y < 0 || \
	ray->cur_map_x >= game->infomap->size_x || ray->cur_map_y < 0)
	{
		res->dist = -1.0;
		res->wall_orientation = 'N';
		res->offset = 0;
		ray->cur_map_x = 0;
		ray->cur_map_y = 0;
		return (1);
	}
	return (0);
}

/* Norminette bypass to start a raycast */
static void	start_ray(t_ray *ray)
{
	alloc_ray_intersections(ray);
	find_vert_inter(ray);
	find_horiz_inter(ray);
	create_inter_array(ray);
}

/* Send a ray from the player position to a specific angle of the map
and return the distance of the first obstacle found on the way and
the offset (modulo 64) for later wall texturing */
void	send_raycast(t_game *game, double ray_ang, t_raysult *res)
{
	t_ray	ray;
	int		i;

	init_raycast(game, &ray, ray_ang, &i);
	start_ray(&ray);
	while (i < ray.size_x + ray.size_y)
	{
		if (ray.order[i][0] != -1.0 && ray.order[i][1] != -1.0)
		{
			calc_map(&ray, ray.order[i][0], ray.order[i][1], ray.order[i][2]);
			if (is_invalid_ray(game, &ray, res))
				break ;
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
