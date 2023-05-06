/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:29:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:44:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_texts_south(t_game *game, t_infomap *infomap)
{
	if (is_texture_path_valid(infomap->so_text) == 0)
		err_msg_and_free_all(ERR_TXT_PATH, game);
	game->so_texture = init_img_struct(game->mlx, CUBES_SIZE,
			CUBES_SIZE, IMPORT);
	if (!game->so_texture)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->so_texture->img = mlx_xpm_file_to_image(game->mlx,
			infomap->so_text, &game->so_texture->width,
			&game->so_texture->height);
	if (!game->so_texture->img)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->so_texture->addr = mlx_get_data_addr(game->so_texture->img,
			&game->so_texture->bits_per_pixel, &game->so_texture->line_length,
			&game->so_texture->endian);
}

void	get_texts_north_south(t_game *game, t_infomap *infomap)
{
	if (is_texture_path_valid(infomap->no_text) == 0)
		err_msg_and_free_all(ERR_TXT_PATH, game);
	game->no_texture = init_img_struct(game->mlx, CUBES_SIZE,
			CUBES_SIZE, IMPORT);
	if (!game->no_texture)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->no_texture->img = mlx_xpm_file_to_image(game->mlx,
			infomap->no_text, &game->no_texture->width,
			&game->no_texture->height);
	if (!game->no_texture->img)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->no_texture->addr = mlx_get_data_addr(game->no_texture->img,
			&game->no_texture->bits_per_pixel, &game->no_texture->line_length,
			&game->no_texture->endian);
	get_texts_south(game, infomap);
}

static void	get_text_east(t_game *game, t_infomap *infomap)
{
	if (is_texture_path_valid(infomap->ea_text) == 0)
		err_msg_and_free_all(ERR_TXT_PATH, game);
	game->ea_texture = init_img_struct(game->mlx, CUBES_SIZE,
			CUBES_SIZE, IMPORT);
	if (!game->ea_texture)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->ea_texture->img = mlx_xpm_file_to_image(game->mlx,
			infomap->ea_text, &game->ea_texture->width,
			&game->ea_texture->height);
	if (!game->ea_texture->img)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->ea_texture->addr = mlx_get_data_addr(game->ea_texture->img,
			&game->ea_texture->bits_per_pixel, &game->ea_texture->line_length,
			&game->ea_texture->endian);
}

void	get_texts_west_east(t_game *game, t_infomap *infomap)
{
	if (is_texture_path_valid(infomap->we_text) == 0)
		err_msg_and_free_all(ERR_TXT_PATH, game);
	game->we_texture = init_img_struct(game->mlx, CUBES_SIZE,
			CUBES_SIZE, IMPORT);
	if (!game->we_texture)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->we_texture->img = mlx_xpm_file_to_image(game->mlx,
			infomap->we_text, &game->we_texture->width,
			&game->we_texture->height);
	if (!game->we_texture->img)
		err_msg_and_free_all(ERR_MALLOC, game);
	game->we_texture->addr = mlx_get_data_addr(game->we_texture->img,
			&game->we_texture->bits_per_pixel, &game->we_texture->line_length,
			&game->we_texture->endian);
	get_text_east(game, infomap);
}
