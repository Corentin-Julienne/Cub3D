/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:14:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/16 12:40:54 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check wether the map relevant infos are actually stored in the struct map_data */

void	print_cub_file(t_map_data *map_data)
{
	int		y = 0;

	printf("------------------------------------------------\n");
	while (map_data->cub && map_data->cub[y])
	{
		printf("|%s|\n", map_data->cub[y]);
		y++;
	}
	printf("------------------------------------------------\n");
}

void	print_infos(t_map_data *map_data)
{
	printf("-----------------------------------------------\n");
	printf("path to the north :   |%s|\n", map_data->no_text);
	printf("path to the south :   |%s|\n", map_data->so_text);
	printf("path to the west  :   |%s|\n", map_data->we_text);
	printf("path to the east  :   |%s|\n", map_data->ea_text);
	printf("ceiling : color 1 : %d | color 2 : %d | color 3 : %d\n",
		map_data->ceil_col[0], map_data->ceil_col[1], map_data->ceil_col[2]);
	printf("floor   : color 1 : %d | color 2 : %d | color 3 : %d\n", map_data->floor_col[0],
		map_data->floor_col[1], map_data->floor_col[2]);
	printf("-----------------------------------------------\n");
}

void	print_oneline(t_map_data *map_data)
{
	printf("%s\n", map_data->lines);
}

void	print_map_infos(t_map_data *map_data)
{
	int			y;
	
	printf("------------------------------\n");
	printf("NORTH TEXTURES PATH = %s\n", map_data->no_text);
	printf("SOUTH TEXTURES PATH = %s\n", map_data->so_text);
	printf("EAST TEXTURES PATH  = %s\n", map_data->ea_text);
	printf("WEST TEXTURES PATH  = %s\n", map_data->we_text);
	printf("CEILING COLORS      = | color 1 : %d | color 2 : %d | color 3 : %d |\n",
		map_data->ceil_col[0], map_data->ceil_col[1], map_data->ceil_col[2]);
	printf("FLOOR COLORS        = | color 1 : %d | color 2 : %d | color 3 : %d |\n\n",
		map_data->floor_col[0], map_data->floor_col[1], map_data->floor_col[2]);
	printf("---------PRINTING MAP---------\n");
	y = 0;
	while (map_data->map[y])
	{
		printf("%s\n", map_data->map[y]);
		y++;
	}
	printf("------------------------------\n");	
}

void	leaks_killing(void)
{
	printf("\n\n---------------------------------------\n");
	printf("---------------[ LEAKS ]---------------\n");
	printf("---------------------------------------\n\n");
	system("leaks Cub3D");
}

void print_split(char **split)
{
	int		i = 0;
	
	while (split[i] != NULL)
	{
		printf("|%s|\n", split[i]);
		i++;
	}
}
