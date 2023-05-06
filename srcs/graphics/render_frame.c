/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:07:05 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 09:37:13 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* render landscape is used to draw floor and ceiling */

static void	render_landscape(t_game *game, int index)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->imgs_set[index]->height)
	{
		x = 0;
		while (x < game->imgs_set[index]->width)
		{
			if (y < (game->imgs_set[index]->height / 2))
			{
				mlx_pixel_put_to_img(game->imgs_set[index],
					x, y, game->col_ceil);
			}
			if (y >= (game->imgs_set[index]->height / 2))
			{
				mlx_pixel_put_to_img(game->imgs_set[index],
					x, y, game->col_floor);
			}
			x++;
		}
		y++;
	}
}

/* choose img is used to check what images should be used (index 0 or 1) 
check wether an img is used and used the other
when no img is used, we use the first image (index 0) */

static int	choose_img(t_game *game)
{
	int				img_index;

	if (game->imgs_set[0] != NULL && game->imgs_set[1] == NULL)
		img_index = 1;
	else
		img_index = 0;
	return (img_index);
}

/* altern_imgs is used after the first frame has been used
it creates another img, then will render the foor and ceiling,
and will then draw the wall using raycasting algo
destroy the former img after putting the actual img to window */

static void	populate_img(t_game *game)
{
	int		img_index;

	img_index = choose_img(game);
	game->imgs_set[img_index] = init_img_struct(game->mlx,
			WDW_WIDTH, WDW_HEIGHT, NEW_IMG);
	render_landscape(game, img_index);
	render_walls(game, img_index, 0, 0);
	render_minimap(game->minimap, game, img_index);
	render_crosshair(game, img_index);
	if (img_index == 0)
	{
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[0]->img, 0, 0);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[1]->img, 0, 0);
	}
	if (img_index == 0)
		clear_mlx_img_struct(&game->imgs_set[1]);
	if (img_index == 1)
		clear_mlx_img_struct(&game->imgs_set[0]);
}

/* render frame render is used to rotate the set of two images.
The first img is used the first time. When player triggers a movement 
(when pressing a key), it triggers window modifcation (using ray casting algo,
with modified position parameters).
The images are used alternatively.
The already existing image is destroyed after the second img is put to the 
window */

int	render_frame(t_game *game)
{
	static bool	first_iter = true;

	if (first_iter == true)
	{
		game->run = true;
		game->imgs_set[0] = init_img_struct(game->mlx,
				WDW_HEIGHT, WDW_HEIGHT, NEW_IMG);
		render_landscape(game, 0);
		render_walls(game, 0, 0, 0);
		render_minimap(game->minimap, game, 0);
		render_crosshair(game, 0);
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[0]->img, 0, 0);
		game->run = false;
		first_iter = false;
	}
	else
	{
		update_player_data(game, game->ply);
		game->run = true;
		populate_img(game);
		game->run = false;
	}
	return (1);
}
