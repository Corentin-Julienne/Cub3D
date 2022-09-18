/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:52:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/18 16:57:32 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	// print_infomap_infos(infomap); // debug functions, kill after	
	game = init_game_struct(infomap);
	if (!game)
		err_msg_and_free(ERR_MALLOC, infomap);
	init_game(game);
	return (0);
}
