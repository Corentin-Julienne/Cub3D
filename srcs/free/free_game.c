/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:31:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/13 13:12:01 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* free the set of two imgs and free it, then set it to NULL */

static void	free_set_of_imgs(t_mlx_img ***imgs_set, t_game *game)
{
	if (*imgs_set == NULL)
		return ;
	if (*imgs_set[0])
		mlx_destroy_image(game->mlx, (*imgs_set[0])->img);
	if (*imgs_set[1])
		mlx_destroy_image(game->mlx, (*imgs_set[1])->img);
	free((*imgs_set));
	**imgs_set = NULL;
}

/* free a given texture and suppress the img within it */

static void	free_texture(t_texture **text, t_game *game)
{
	if (*text == NULL)
		return ;
	mlx_destroy_image(game->mlx, (*text)->img);
	free(*text);
	*text = NULL;
}

/* free the struct in order to avoid leaks
use when normal program termination or when there is an error */

void	free_map(t_infomap **infomap)
{
	t_infomap		*tmp;

	tmp = *infomap;
	if (!tmp)
		return ;
	free_and_nullify((void **)&tmp->lines);
	if (tmp->cub != NULL)
		free_split(&tmp->cub);
	if (tmp->map != NULL)
		free_split(&tmp->map);
	free_and_nullify((void **)&tmp->no_text);
	free_and_nullify((void **)&tmp->so_text);
	free_and_nullify((void **)&tmp->ea_text);
	free_and_nullify((void **)&tmp->we_text);
	free_and_nullify((void **)&tmp->floor_col);
	free_and_nullify((void **)&tmp->ceil_col);
	free(*infomap);
	*infomap = NULL;
}

/* free the game struct when finishing program
or because of an error (leak unfriendly) */

void	free_game(t_game **game)
{
	t_game			*tmp;

	tmp = *game;
	if (!tmp)
		return ;
	free_set_of_imgs(&tmp->imgs_set, tmp);
	free_map(&tmp->infomap);
	free_texture(&tmp->no_texture, tmp);
	free_texture(&tmp->so_texture, tmp);
	free_texture(&tmp->ea_texture, tmp);
	free_texture(&tmp->we_texture, tmp);
	free_and_nullify((void **)&tmp->keys);
	free((*game)->player);
	(*game)->player = NULL;
	free(*game);
	*game = NULL;
}
