/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 06:42:04 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/10/21 09:43:21 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Get the wall orientation depending on the player position, the ray
final position and the ray angle */
void	calc_wall_orientation(t_ray *ray, t_raysult *res, int i)
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

/* Calculate the actual intersection for vertical lines */
static void	calc_vert(t_ray *ray, double *dist, double *x, double *y)
{
	if (ray->ang > 90 && ray->ang < 270)
	{
		if (*dist == 0)
			*dist = CUBES_SIZE;
		*x -= *dist;
	}
	else
		*x += CUBES_SIZE - *dist;
	*x = ceil_double(*x);
	if (ray->ang == 0 || ray->ang == 180)
		*y = ray->start_y;
	else
		*y = ceil_double(ray->start_y - (*x - ray->start_x) * tan(ray->rad));
}

/* Find every intersection on vertical lines (moving left/right on the X axis)
and put everything in an array */
void	find_vert_inter(t_ray *ray)
{
	double		x;
	double		y;
	double		dist;
	int			idx;

	if (ray->ang == 90 || ray->ang == 270)
		return ;
	idx = 0;
	x = ray->start_x;
	while (x < ray->size_x * CUBES_SIZE && x > 0)
	{
		dist = fmod(x, CUBES_SIZE);
		calc_vert(ray, &dist, &x, &y);
		if (y < 0 || y > ray->size_y * CUBES_SIZE)
			break ;
		ray->found_vert[idx][0] = x;
		ray->found_vert[idx][1] = y;
		idx++;
	}
}

/* Calculate the actual intersection for horizontal lines */
static void	calc_horiz(t_ray *ray, double *dist, double *x, double *y)
{
	if (ray->ang >= 0 && ray->ang <= 180)
	{
		if (*dist == 0)
			*dist = CUBES_SIZE;
		*y -= *dist;
	}
	else
		*y += CUBES_SIZE - *dist;
	*y = ceil_double(*y);
	if (ray->ang == 90 || ray->ang == 270)
		*x = ray->start_x;
	else
		*x = ceil_double(ray->start_x - (*y - ray->start_y) / tan(ray->rad));
}

/* Find every intersection on horizontal lines (moving up/down on the Y axis)
and put everything in an array */
void	find_horiz_inter(t_ray *ray)
{
	double	x;
	double	y;
	double	dist;
	int		idx;

	if (ray->ang == 0 || ray->ang == 180)
		return ;
	idx = 0;
	y = ray->start_y;
	while (y < ray->size_y * CUBES_SIZE && y > 0)
	{
		dist = fmod(y, CUBES_SIZE);
		calc_horiz(ray, &dist, &x, &y);
		if (x < 0 || x > ray->size_x * CUBES_SIZE)
			break ;
		ray->found_horiz[idx][0] = x;
		ray->found_horiz[idx][1] = y;
		idx++;
	}
}
