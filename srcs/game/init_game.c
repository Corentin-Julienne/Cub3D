/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:02:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/18 16:58:42 by cjulienn         ###   ########.fr       */
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

/* init game is the starting point of the game
it triggers event handler and start the game itself with mlx_loop() */

void	init_game(t_game *game)
{
	// put hooks after these
	mlx_hook(game->wdw, 17, 0, exit_hook, &game);
	// should trigger the drawing process on the windows
	render_frame(game);
	// init program
	mlx_loop(game->mlx);
}
