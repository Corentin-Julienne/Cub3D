/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/19 11:09:53 by cjulienn         ###   ########.fr       */
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
