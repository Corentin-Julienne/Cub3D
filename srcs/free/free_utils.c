/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:29:05 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:25:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* free and put it to NULL, only and only if previously allocated */

void	free_and_nullify(void **to_free)
{
	if (to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

/* in case of a probleme of alloc during the split,
use that func to free every malloqued str in the array,
then the array itself */

void	free_problem_str_arr(char ***split, int i)
{
	int			j;
	char		**arr;

	arr = *split;
	j = 0;
	while (j < i)
	{
		free(arr[j]);
		arr[j] = NULL;
		j++;
	}
	free(*split);
	*split = NULL;
}

/* free the product of a ft_split. Free every string in the array,
and then the array itself */

void	free_split(char ***split)
{
	size_t		i;
	char		**arr;

	arr = *split;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

/* clear_mlx_img_struct destroy the img and free the struct */

void	clear_mlx_img_struct(t_img **mlx_img)
{
	mlx_destroy_image((*mlx_img)->mlx, (*mlx_img)->img);
	free(*mlx_img);
	*mlx_img = NULL;
}
