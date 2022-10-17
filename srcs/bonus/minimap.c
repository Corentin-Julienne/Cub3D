/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:50:51 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 06:46:34 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* render the player when map is small enough to be displayed entirely */

static void	render_player(t_minimap *mini, t_game *game)
{
	int			scale;
	int			center_x;
	int			center_y;
	int			x;
	int			y;

	scale = CUBES_SIZE / mini->edge_len;
	center_x = (int)round(game->ply->pos_x / scale);
	center_y = (int)round(game->ply->pos_y / scale);
	y = center_y - 2;
	while (y < center_y + 2)
	{
		x = center_x - 2;
		while (x < center_x + 2)
		{
			mlx_pixel_put_to_img(game->imgs_set[mini->img_index],
				x + mini->offset + mini->padding_x,
				y + mini->offset + mini->padding_y,
				mini->col_ply);
			x++;
		}
		y++;
	}
}

/* the padding is updated for the minimap
to be centered around the backgroud */

static void	update_padding(t_minimap *mini, t_infomap *infomap)
{
	mini->padding_x = (mini->width - infomap->size_x * mini->edge_len) / 2;
	if (mini->padding_x < 5)
		mini->padding_x = 5;
	mini->padding_y = (mini->height - infomap->size_y * mini->edge_len) / 2;
	if (mini->padding_y < 5)
		mini->padding_y = 5;
}

static void	draw_minimap(t_minimap *mini, t_game *game, char **map)
{
	int			x;
	int			y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				render_square(mini, game,
					(x * mini->edge_len) + mini->offset + mini->padding_x,
					(y * mini->edge_len) + mini->offset + mini->padding_y);
			x++;
		}
		y++;
	}
}

/* check wether the minimap fits the minimap background. Try to downsize it 
to reasonably tiny proportions if not the case. If map is too big and/or 
window is too small, simply does not display minimap */

void	render_minimap(t_minimap *mini, t_game *game, int img_index)
{
	if (mini->edge_len <= 2)
		return ;
	mini->img_index = img_index;
	render_background(mini, game, img_index);
	update_padding(mini, game->infomap);
	draw_minimap(mini, game, game->infomap->map);
	render_player(mini, game);
}

void	init_minimap_struct(t_game *game)
{
	t_minimap		*mini;

	mini = (t_minimap *)malloc(sizeof(t_minimap));
	if (!mini)
		err_msg_and_free_all(ERR_MALLOC, game);
	mini->width = game->wdw_x / 4;
	mini->height = game->wdw_y / 4;
	mini->offset = 10;
	mini->padding_x = 5;
	mini->padding_y = 5;
	mini->edge_len = 8;
	mini->col_back = 0x0000000;
	mini->col_ply = 0x0FF0000;
	mini->col_square = 0x0FFFFFF;
	while (!is_map_fitting(mini, game) && mini->edge_len > 2)
		mini->edge_len -= 2;
	game->minimap = mini;
}
