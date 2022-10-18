/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:45:23 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 11:49:23 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* free ray allocated data in case of any problem */
void	free_ray_when_problem(t_ray *ray, char *spec)
{
	int			i;

	i = -1;
	if (ray->found_vert)
	{
		while (ray->found_vert[++i] && i < ray->size_x)
			free(ray->found_vert[i]);
		free(ray->found_vert);
	}
	i = -1;
	if (ray->found_horiz)
	{
		while (ray->found_horiz[++i] && i < ray->size_y)
			free(ray->found_horiz[i]);
		free(ray->found_horiz);
	}
	i = -1;
	if (ray->order)
	{
		while (ray->order[++i] && i < (ray->size_x + ray->size_y))
			free(ray->order[i]);
		free(ray->order);
	}	
	err_msg_and_free_all(spec, ray->game);
}

/* Free intersections arrays */
void	free_ray_intersections(t_ray *ray)
{
	int	i;

	i = 0;
	while (i < ray->size_x)
		free(ray->found_vert[i++]);
	free(ray->found_vert);
	i = 0;
	while (i < ray->size_y)
		free(ray->found_horiz[i++]);
	free(ray->found_horiz);
	i = 0;
	while (i < ray->size_x + ray->size_y)
		free(ray->order[i++]);
	free(ray->order);
}
