/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:52:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/15 15:36:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map_data			*map_data;

	// atexit(leaks_killing); // debug functions, kill after use
	if (argc != 2)
		print_err_msg(ERR_NB_ARGS);
	map_data = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map_data)
		exit(EXIT_FAILURE);
	init_map_data(map_data, argv[1]);
	print_map_infos(map_data); // debug functions, kill after
	return (0);
}
