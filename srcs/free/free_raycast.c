/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:45:23 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 06:43:52 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* free and put to NULL an array of double, 
should it have been allocated before */

static void	free_double_arr(double ***arr, int stop)
{
	int			i;
	double		**tmp;

	if (*arr == NULL)
		return ;
	tmp = *arr;
	i = 0;
	while (i < stop)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

/* free the raycast struct every frame to ensure values are not used twice */

void	free_raycast(t_ray **ray)
{
	t_ray			*tmp;

	tmp = *ray;
	if (!tmp)
		return ;
	if (tmp->map)
		free_split(&tmp->map);
	free_double_arr(&tmp->found_horiz, tmp->size_x);
	free_double_arr(&tmp->found_vert, tmp->size_y);
	free_double_arr(&tmp->order, tmp->size_x + tmp->size_y);
	free(*ray);
	*ray = NULL;
}
