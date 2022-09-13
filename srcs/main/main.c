/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:52:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 15:49:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map_data			*map_data;

	if (argc != 2)
		print_err_msg(NB_ARG_ERR);
	
	map_data = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map_data)
		exit(EXIT_FAILURE);
	init_map_data(map_data, argv[1]);
	
	return (0);
}
