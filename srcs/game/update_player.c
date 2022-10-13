/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:06:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/14 01:02:11 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// typedef struct s_player {
// 	double		pos_x;
// 	double		pos_y;
// 	double		ang_y; // Rotation of the camera horizontally
// 	double		dist_from_proj; // Distance between the viewer and the projection screen
// 	t_game		*game;
// }				t_player;

/* update_player_data is used to modify the player data
(position and angle), when the WASD and directional arrows 
are pressed */

void	update_player_data(t_game *game, t_player *ply)
{
	double	prev_pos_x;
	double	prev_pos_y;

	prev_pos_x = ply->pos_x;
	prev_pos_y = ply->pos_y;

    if (game->keys[4])
        ply->ang_y -= 2;
    if (game->keys[5])
        ply->ang_y += 2;

	if (game->keys[0] == true) // Z - avancer
	{
		ply->pos_x += cos(ply->ang_y * M_PI / 180) * 3;
		ply->pos_y -= sin(ply->ang_y * M_PI / 180) * 3;
	}
	if (game->keys[1] == true) // S - reculer
	{
		ply->pos_x -= cos(ply->ang_y * M_PI / 180) * 3;
		ply->pos_y += sin(ply->ang_y * M_PI / 180) * 3;
	}
	if (game->keys[2] == true) // D - droite
	{
		ply->pos_x += cos((ply->ang_y + 90) * M_PI / 180) * 3;
		ply->pos_y -= sin((ply->ang_y + 90) * M_PI / 180) * 3;
	}
	if (game->keys[3] == true) // D - gauche
	{
		ply->pos_x += cos((ply->ang_y - 90) * M_PI / 180) * 3;
		ply->pos_y -= sin((ply->ang_y - 90) * M_PI / 180) * 3;
	}

	/* If this is out of the map, we put the player back to his previous position */
	if (game->infomap->map[(int)ply->pos_y / CUBES_SIZE][(int)ply->pos_x / CUBES_SIZE] == '1')
	{
		ply->pos_x = prev_pos_x;
		ply->pos_y = prev_pos_y;
	}
}
