/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/02 02:53:26 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d"

/* Initialize the player at the correct position and angle */
void    init_player(t_game *game, int x, int y)
{
    t_player    *player;

    player = malloc(sizeof(t_player));
    if (!player)
        err_msg_and_freeall(ERR_MALLOC, game);
    player->x = (double)x;
    player->y = (double)y;
    player->ang_y = 0;
    game->player = player;
}