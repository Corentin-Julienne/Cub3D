/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:06:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/11 16:26:27 by cjulienn         ###   ########.fr       */
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

void	update_player_data(t_game *game, t_player *ply) // to test and update
{
	if (game->keys[0] == true)
		ply->pos_x--;
	if (game->keys[1] == true)
		ply->pos_y--;
	if (game->keys[2] == true)
		ply->pos_x++;
	if (game->keys[3] == true)
		ply->pos_y++;
	if (game->keys[4] == true)
        ply->ang_y -= 1;
    if (game->keys[5] == true)
        ply->ang_y += 1;
}
