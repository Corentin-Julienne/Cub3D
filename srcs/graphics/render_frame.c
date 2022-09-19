/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:07:05 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/19 16:48:10 by cjulienn         ###   ########.fr       */
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
	int		img_index;

	if (game->imgs_set[0] != NULL && game->imgs_set[1] == NULL)
		img_index = 1;
	else
		img_index = 0;
	return (img_index);
}

static void	altern_imgs(t_game *game)
{
	int		img_index;

	img_index = choose_img(game);
	game->imgs_set[img_index] = init_mlx_img_struct(game->mlx,
		WDW_WIDTH, WDW_HEIGHT);
	render_landscape(game, img_index);
	// add algo to render walls after this line
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
The first img is used the first time. When player triggers a movement,
it renders another frame. The images are used alternatively. 
The already existing image is destroyed after the second img is put to the 
window */

int	render_frame(t_game *game) // to debug
{
	static bool	first_iter = true;

	if (first_iter == true)
	{
		game->imgs_set[0] = init_mlx_img_struct(game->mlx,
			WDW_HEIGHT, WDW_HEIGHT);
		render_landscape(game, 0);
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[0]->img, 0, 0);
		first_iter = false;
	}
	else
		altern_imgs(game);
	return (0);
}