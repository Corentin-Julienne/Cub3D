/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/19 13:02:35 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Find the position of a character in the map or -1 if not found */
int	get_char_map_pos(char **map, char c, int ret_x)
{
	int				x;
	int				y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
			{
				if (ret_x)
					return (x);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

/* Initialize the player at the correct position and angle */
static void	init_player_struct(t_game *game, int right_x, int top_y, int ang)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		err_msg_and_free_all(ERR_MALLOC, game);
	player->pos_x = (double)(right_x * CUBES_SIZE + CUBES_SIZE / 2);
	player->pos_y = (double)(top_y * CUBES_SIZE + CUBES_SIZE / 2);
	player->ang_y = (double)ang;
	player->dist_from_proj = (double)((game->wdw_x / 2)
			/ tanf((PLY_VIEW_FOV_DEG / 2) * M_PI / 180));
	game->ply = player;
}

/* Find and create the initial player on the position from the map */
void	init_player(t_game *game)
{
	int			right_x;
	int			top_y;
	int			i;
	char		chars[4];

	chars[0] = 'W';
	chars[1] = 'N';
	chars[2] = 'E';
	chars[3] = 'S';
	i = 0;
	while (i < 4)
	{
		right_x = get_char_map_pos(game->infomap->map, chars[i], 1);
		top_y = get_char_map_pos(game->infomap->map, chars[i], 0);
		if (right_x != -1 && top_y != -1)
		{
			init_player_struct(game, right_x, top_y, i * 90);
			return ;
		}
		i++;
	}
	return (err_msg_and_free_all(ERR_PARAM_NB, game));
}
