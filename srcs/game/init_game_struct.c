/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/23 12:14:45 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* get_colors convert the colors of ceil and floor from trgb 
to a sole integer to be able to use it whith minilibx functions */

static void	get_colors(t_game *game)
{
	game->col_ceil = rtn_ceil_and_floor_colors(game->infomap, CEILING);
	free(game->infomap->ceil_col);
	game->infomap->ceil_col = NULL;
	game->col_floor = rtn_ceil_and_floor_colors(game->infomap, FLOOR);
	free(game->infomap->floor_col);
	game->infomap->floor_col = NULL;
}

/* get_key_bools allow to store booleans in an array to check
whether the keyboard keys WASD are actually pressed or not */

static bool	*get_key_bools(t_game *game)
{
	bool			*bool_arr;
	int				i;

	bool_arr = (bool *)malloc(sizeof(bool) * 4);
	if (!bool_arr)
	{
		free(game->imgs_set);
		free(game);
		return (NULL);
	}
	i = 0;
	while (i < 4)
	{
		bool_arr[i] = false;
		i++;
	}
	return (bool_arr);
}

/* init_game_struct init the minilibx, create a window,
store its heigth and width, and create an array of mlx_imgs
for further use */

t_game	*init_game_struct(t_infomap *infomap)
{
	t_game			*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->imgs_set = (t_mlx_img **)malloc(sizeof(t_mlx_img *) * 2);
	if (!game->imgs_set)
	{
		free(game);
		return (NULL);
	}
	game->keys = get_key_bools(game);
	if (!game->keys)
		return (NULL);
	game->imgs_set[0] = NULL;
	game->imgs_set[1] = NULL;
	game->infomap = infomap;
	game->mlx = mlx_init();
	game->wdw_x = WDW_WIDTH;
	game->wdw_y = WDW_HEIGHT;
	game->wdw = mlx_new_window(game->mlx, game->wdw_x, game->wdw_y, "Cub3D");
	get_colors(game);
	return (game);
}
