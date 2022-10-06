/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/06 03:01:03 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Find the position of a character in the map or -1 if not found */
int get_char_map_pos(char **map, char c, int ret_x)
{
    int x;
    int y;

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
static void    init_player_struct(t_game *game, int right_x, int top_y)
{
    t_player    *player;

    player = malloc(sizeof(t_player));
    if (!player)
        err_msg_and_free_all(ERR_MALLOC, game);
    player->pos_x = (double)(right_x * CUBES_SIZE + CUBES_SIZE / 2);
    player->pos_y = (double)(top_y * CUBES_SIZE + CUBES_SIZE / 2);
    player->ang_y = (double)135;
    player->dist_from_proj = (double)((game->wdw_x / 2) / tan(PLY_VIEW_FOV_DEG / 2));
    game->player = player;

    // Hello there buddy
    // This is the past Maxime that is writing. Right now I'm going to bed so I decide to write you this important note.
    // The angle is globally working correctly and the algorithm seems fine.
    // However, there is a problem when the wall is aiming at the left side of the map, 
    // the x hitpos is set to 0 but it should not be possible since 0 is "behind" the wall.
    //
    // This is probably caused by the fact that I floor the hit point at some time.
    // So please fix that shit

    // TEMPORARY - Don't put that here weirdo
    printf("\nPlayer initialized at pos (%f, %f) with angle %f\n", player->pos_x, player->pos_y, player->ang_y);
    t_raycast cast;
    raycast(game, &cast);
    printf("-> Our ray has hit a wall at pos (%f, %f) with angle %f\n\n", cast.wall_touch_x, cast.wall_touch_y, player->ang_y);
}

/* Find and create the initial player on the position from the map */
void    init_player(t_game *game)
{
    int right_x;
    int top_y;

    right_x = get_char_map_pos(game->infomap->map, 'N', 1);
    top_y = get_char_map_pos(game->infomap->map, 'N', 0);
    init_player_struct(game, right_x, top_y);
}