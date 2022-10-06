/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:52:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/05 14:18:51 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_infomap			*infomap;
	t_game				*game;

	// atexit(leaks_killing); // debug functions, kill after use
	if (argc != 2)
		print_err_msg(ERR_NB_ARGS);
	infomap = (t_infomap *)malloc(sizeof(t_infomap));
	if (!infomap)
		exit(EXIT_FAILURE); // PERSONNALIZED MSG ?
	init_infomap_struct(infomap, argv[1]);
	print_infomap_infos(infomap); // debug functions, kill after	
	game = init_game_struct(infomap);
	if (!game)
		err_msg_and_free(ERR_MALLOC, infomap);
	init_player(game);
	init_game(game);
	return (0);
}
