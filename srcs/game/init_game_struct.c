/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:33:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* get_key_bools allow to store booleans in an array to check
whether the keyboard keys WASD are actually pressed or not */

static bool	*get_key_bools(void)
{
	bool			*bool_arr;
	int				i;

	bool_arr = (bool *)malloc(sizeof(bool) * 7);
	if (!bool_arr)
		return (NULL);
	i = 0;
	while (i < 7)
	{
		bool_arr[i] = false;
		i++;
	}
	return (bool_arr);
}

/* put every pointer in the struct to NULL to be able to
manage it more freely and safely in case of problem/deletion */

static void	protect_game_struct(t_game *game)
{
	game->imgs_set = NULL;
	game->infomap = NULL;
	game->wdw = NULL;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	game->keys = NULL;
	game->ply = NULL;
	game->minimap = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		err_msg_and_free_all(ERR_MLX, game);
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
	protect_game_struct(game);
	game->imgs_set = (t_img **)malloc(sizeof(t_img *) * 2);
	if (!game->imgs_set)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->imgs_set[0] = NULL;
	game->imgs_set[1] = NULL;
	get_texts_north_south(game, infomap);
	get_texts_west_east(game, infomap);
	game->keys = get_key_bools();
	if (!game->keys)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->run = false;
	game->infomap = infomap;
	game->wdw_x = WDW_WIDTH;
	game->wdw_y = WDW_HEIGHT;
	game->wdw = mlx_new_window(game->mlx, game->wdw_x, game->wdw_y, "Cub3D");
	get_colors(game);
	return (game);
}
