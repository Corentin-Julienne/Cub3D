/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:50:51 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/14 10:44:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_minimap
{
	int			width;
	int			height;
	int			offset;
	int			padding_x;
	int			padding_y;
	int			img_index;
	int			edge_len;
	int			col_back;
	int			col_square;
	int			col_ply;
}				t_minimap;

/* check wether the minimap is big enough to display the entire 
map. Return 1 if it is the case, o otherwise*/

static int	is_map_fitting(t_minimap *mini, t_game *game) 
{
	if (mini->width + (mini->padding_x * 2) < game->infomap->size_x * 4)
		return (0);
	if (mini->height + (mini->padding_y * 2) < game->infomap->size_y * 4)
		return (0);
	return (1);
}

static int	is_within_minimap(t_minimap *mini, int x, int y)
{
	if (x < mini->offset + mini->padding_x || x > mini->offset + mini->width)
		return (0);
	if (y < mini->offset + mini->padding_y || y > mini->offset + mini->height)
		return (0);
	return (1);
}

static void	render_player(t_minimap *mini, t_game *game) // to polish
{
	int			scale;
	int			x;
	int			y;

	scale = CUBES_SIZE / mini->edge_len;
	x = (int)round(game->player->pos_x / scale);
	y = (int)round(game->player->pos_y / scale);
	mlx_pixel_put_to_img(game->imgs_set[mini->img_index],
		x + mini->offset + mini->padding_x,
		y + mini->offset + mini->padding_y,
		mini->col_ply);
}

static void render_square(t_minimap *mini, t_game *game, int x, int y)
{
	int			i;
	int			j;

	j = 0;
	while (y + j < y + mini->edge_len)
	{
		i = 0;
		while (x + i < x + mini->edge_len)
		{
			if (is_within_minimap(mini, x + i, y + j) == 1)
			{
				mlx_pixel_put_to_img(game->imgs_set[mini->img_index],
					x + i, y + j, mini->col_square);
			}
			i++;
		}
		j++;
	}
}

static void	render_background(t_minimap *mini,
				t_game *game, int img_index)
{
	int		i;
	int		j;

	j = 0;
	while (j < mini->height)
	{
		i = 0;
		while (i < mini->width)
		{
			mlx_pixel_put_to_img(game->imgs_set[img_index],
				i + mini->offset, j + mini->offset, mini->col_back);
			i++;
		}
		j++;
	}
}

static t_minimap	*init_minimap_struct(t_game *game, int img_index)
{
	t_minimap 		*mini;

	mini = (t_minimap *)malloc(sizeof(t_minimap));
	if (!mini)
		err_msg_and_free_all(ERR_MALLOC, game);
	mini->width = game->wdw_x / 4;
	mini->height = game->wdw_y / 4;
	mini->offset = 10;
	mini->padding_x = 5;
	mini->padding_y = 5;
	mini->img_index = img_index;
	mini->edge_len = 8;
	mini->col_back = 0x0000000;
	mini->col_ply = 0x0FF0000;
	mini->col_square = 0x0FFFFFF;
	return (mini);
}

static void	update_padding(t_minimap *mini, t_infomap *infomap)
{
	mini->padding_x = (mini->width - (infomap->size_x * mini->edge_len)) / 2;
	mini->padding_y = (mini->height - (infomap->size_y * mini->edge_len)) / 2;
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

void	draw_player_surroundings(t_minimap *mini, t_game *game, char **map) // to finish
{
	int				x;
	int				y;
	
	mlx_pixel_put_to_img(game->imgs_set[mini->img_index],
		mini->offset + (mini->width / 2), mini->offset + (mini->height / 2),
		mini->col_ply);
}

void	render_minimap(t_game *game, int img_index)
{
	t_minimap		*mini;

	mini = init_minimap_struct(game, img_index);
	render_background(mini, game, img_index);
	if (is_map_fitting(mini, game))
	{
		update_padding(mini, game->infomap);
		draw_minimap(mini, game, game->infomap->map);
		render_player(mini, game);
	}
	else
		draw_player_surroundings(mini, game, game->infomap->map);
	free(mini);
}
