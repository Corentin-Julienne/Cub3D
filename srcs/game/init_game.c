/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:02:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/23 12:23:39 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* allow to terminate window when the red cross is pressed */

static int	exit_hook(t_game **game)
{
	mlx_destroy_window((*game)->mlx, (*game)->wdw);
	free_map((*game)->infomap);
	free(*game);
	exit(EXIT_SUCCESS);
	return (1);
}

/* key_press_hook is triggered when a key is pressed
put the booleans to true, and will allow
the mlx_hoop_look to modify the display of the maze 
when escape is pressed, terminate the game */

static int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys[0] = true;
	else if (keycode == 1)
		game->keys[1] = true;
	else if (keycode == 2)
		game->keys[2] = true;
	else if (keycode == 0)
		game->keys[3] = true;
	else if (keycode == 53) // optimize this
	{
		mlx_destroy_window(game->mlx, game->wdw); 
		free_map(game->infomap);
		free(game);
		exit(EXIT_SUCCESS);
	}
	return (0);	
}

/* key_release_hook is activated when keys WASD are released
indicate to the render_frame function that key is not activated 
any more */

static int key_release_hook(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys[0] = false;
	else if (keycode == 1)
		game->keys[1] = false;
	else if (keycode == 2)
		game->keys[2] = false;
	else if (keycode == 0)
		game->keys[3] = false;
	return (0);
}

/* init game is the starting point of the game
it triggers event handler hooks and start the game itself 
with mlx_loop() */

void	init_game(t_game *game)
{
	mlx_hook(game->wdw, 17, 0, exit_hook, &game);
	mlx_hook(game->wdw, 2, 0, key_press_hook, game);
	mlx_hook(game->wdw, 2, 0, key_release_hook, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}
