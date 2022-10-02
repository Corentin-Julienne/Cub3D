/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/02 02:53:48 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* get_key_bools allow to store booleans in an array to check
whether the keyboard keys WASD are actually pressed or not */

static bool	*get_key_bools(t_game *game)
{
	bool			*bool_arr;
	int				i;

	bool_arr = (bool *)malloc(sizeof(bool) * 6);
	if (!bool_arr) // change this
	{
		free(game->imgs_set);
		free(game);
		return (NULL);
	}
	i = 0;
	while (i < 6)
	{
		bool_arr[i] = false;
		i++;
	}
	return (bool_arr);
}

static void get_texts_north_south(t_game *game, t_infomap *infomap)
{
	game->no_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!game->no_texture)
		printf("problem there\n"); // handle that shit
	game->no_texture->img = mlx_xpm_file_to_image(game->mlx,
		infomap->no_text, &game->no_texture->width, &game->no_texture->height);
	if (!game->no_texture->img)
		printf("problem there\n");// handle that shit
	game->so_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!game->so_texture)
		printf("problem there\n"); // handle that shit
	game->so_texture->img = mlx_xpm_file_to_image(game->mlx,
		infomap->so_text, &game->so_texture->width, &game->so_texture->height);
	if (!game->so_texture->img)
		printf("problem there\n"); // handle that shit
}

static void	get_texts_west_east(t_game *game, t_infomap *infomap)
{
	game->we_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!game->we_texture)
		printf("problem there\n"); // handle that shit
	game->we_texture->img = mlx_xpm_file_to_image(game->mlx,
		infomap->we_text, &game->we_texture->width, &game->we_texture->height);
	if (!game->we_texture->img)
		printf("problem there\n");// handle that shit
	game->ea_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!game->ea_texture)
		printf("problem there\n"); // handle that shit
	game->ea_texture->img = mlx_xpm_file_to_image(game->mlx,
		infomap->ea_text, &game->ea_texture->width, &game->ea_texture->height);
	if (!game->ea_texture->img)
		printf("problem there\n"); // handle that shit
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
	game->player = NULL;
	game->mlx = mlx_init();
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
	game->imgs_set = (t_mlx_img **)malloc(sizeof(t_mlx_img *) * 2);
	if (!game->imgs_set)
		{}; // handle this with appropriate function
	game->imgs_set[0] = NULL;
	game->imgs_set[1] = NULL;
	get_texts_north_south(game, infomap);
	get_texts_west_east(game, infomap);
	game->keys = get_key_bools(game);
	if (!game->keys)
		{}; // handle this with appropiate function
	game->infomap = infomap;
	game->wdw_x = WDW_WIDTH;
	game->wdw_y = WDW_HEIGHT;
	game->wdw = mlx_new_window(game->mlx, game->wdw_x, game->wdw_y, "Cub3D");
	get_colors(game);
	return (game);
}
