/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:14:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/10 15:45:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check wether the map relevant infos are actually stored in the struct map */

void	print_cub_file(t_infomap *infomap)
{
	int		y = 0;

	printf("------------------------------------------------\n");
	while (infomap->cub && infomap->cub[y])
	{
		printf("|%s|\n", infomap->cub[y]);
		y++;
	}
	printf("------------------------------------------------\n");
}

void	print_infos(t_infomap *infomap)
{
	printf("-----------------------------------------------\n");
	printf("path to the north :   |%s|\n", infomap->no_text);
	printf("path to the south :   |%s|\n", infomap->so_text);
	printf("path to the west  :   |%s|\n", infomap->we_text);
	printf("path to the east  :   |%s|\n", infomap->ea_text);
	printf("ceiling : color 1 : %d | color 2 : %d | color 3 : %d\n",
		infomap->ceil_col[0], infomap->ceil_col[1], infomap->ceil_col[2]);
	printf("floor   : color 1 : %d | color 2 : %d | color 3 : %d\n", infomap->floor_col[0],
		infomap->floor_col[1], infomap->floor_col[2]);
	printf("-----------------------------------------------\n");
}

void	print_oneline(t_infomap *infomap)
{
	printf("%s\n", infomap->lines);
}

void	print_infomap_infos(t_infomap *infomap)
{
	int			y;
	
	printf("------------------------------\n");
	printf("NORTH TEXTURES PATH = %s\n", infomap->no_text);
	printf("SOUTH TEXTURES PATH = %s\n", infomap->so_text);
	printf("EAST TEXTURES PATH  = %s\n", infomap->ea_text);
	printf("WEST TEXTURES PATH  = %s\n", infomap->we_text);
	printf("CEILING COLORS      = | color 1 : %d | color 2 : %d | color 3 : %d |\n",
		infomap->ceil_col[0], infomap->ceil_col[1], infomap->ceil_col[2]);
	printf("FLOOR COLORS        = | color 1 : %d | color 2 : %d | color 3 : %d |\n\n",
		infomap->floor_col[0], infomap->floor_col[1], infomap->floor_col[2]);
	printf("---------PRINTING MAP---------\n");
	y = 0;
	while (infomap->map[y])
	{
		printf("%s\n", infomap->map[y]);
		y++;
	}
	printf("map size (x) = %d and map size (y) = %d\n", infomap->size_x, infomap->size_y);
	printf("------------------------------\n");	
}

void	leaks_killing(void)
{
	printf("\n\n---------------------------------------\n");
	printf("---------------[ LEAKS ]---------------\n");
	printf("---------------------------------------\n\n");
	// system("leaks Cub3D");
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

void put_xpm_img_to_test(t_game *game) // does not work with small windows
{
	game = (t_game *)game;
	// mlx_put_image_to_window(game->mlx, game->wdw, game->no_texture->img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->wdw, game->so_texture->img, 60, 60);
	// mlx_put_image_to_window(game->mlx, game->wdw, game->ea_texture->img, 120, 120);
	// mlx_put_image_to_window(game->mlx, game->wdw, game->we_texture->img, 180, 180);
}
