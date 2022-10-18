/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:02:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:29:43 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* destroy window and exit without leaks (may have minilibx leaks) */

static void	exit_process(t_game **game)
{
	while (42)
	{
		if ((*game)->run == false)
			break ;
	}
	mlx_destroy_window((*game)->mlx, (*game)->wdw);
	free_game(game);
	exit(EXIT_SUCCESS);
}

/* allow to terminate window when the red cross is pressed */

static int	exit_hook(t_game **game)
{
	exit_process(game);
	return (1);
}

/* key_press_hook is triggered when a key is pressed
put the booleans to true, and will allow
the mlx_hoop_look to modify the display of the maze 
when escape is pressed, terminate the game 
the index 0 to 5 are respectively assignated to WASD keys
and left and right directional arrows */

static int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys[0] = true;
	else if (keycode == A_KEY)
		game->keys[1] = true;
	else if (keycode == S_KEY)
		game->keys[2] = true;
	else if (keycode == D_KEY)
		game->keys[3] = true;
	else if (keycode == LEFT_ARROW)
		game->keys[4] = true;
	else if (keycode == RIGHT_ARROW)
		game->keys[5] = true;
	else if (keycode == SHIFT_KEY)
		game->keys[6] = true;
	else if (keycode == ESCAPE)
		exit_process(&game);
	return (0);
}

/* key_release_hook is activated when keys WASD and left and right
directionnal arrows are released
indicate to the render_frame function that key is not activated 
any more */

static int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys[0] = false;
	else if (keycode == A_KEY)
		game->keys[1] = false;
	else if (keycode == S_KEY)
		game->keys[2] = false;
	else if (keycode == D_KEY)
		game->keys[3] = false;
	else if (keycode == LEFT_ARROW)
		game->keys[4] = false;
	else if (keycode == RIGHT_ARROW)
		game->keys[5] = false;
	else if (keycode == SHIFT_KEY)
		game->keys[6] = false;
	return (0);
}

/* init game is the starting point of the game
it triggers event handler hooks and start the game itself 
with mlx_loop() */

void	init_game(t_game *game)
{
	mlx_hook(game->wdw, EXIT_HOOK, 0, exit_hook, &game);
	mlx_hook(game->wdw, KEY_PRESS_HOOK, 0, key_press_hook, game);
	mlx_hook(game->wdw, KEY_RELEASE_HOOK, 0, key_release_hook, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}
