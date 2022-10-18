/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:52:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:32:33 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_infomap			*infomap;
	t_game				*game;

	if (argc != 2)
		print_err_msg(ERR_NB_ARGS);
	infomap = (t_infomap *)malloc(sizeof(t_infomap));
	if (!infomap)
		print_err_msg(ERR_MALLOC);
	init_infomap_struct(infomap, argv[1]);
	game = init_game_struct(infomap);
	if (!game)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	init_player(game);
	init_minimap_struct(game);
	init_game(game);
	return (0);
}
