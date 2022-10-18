/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:14:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:25:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	printf("---------PRINTING MAP---------\n\n");
	printf("    0123456789\n\n");
	y = 0;
	while (infomap->map[y])
	{
		printf("%d   %s\n", y, infomap->map[y]);
		y++;
	}
	printf("\nmap size (x) = %d and map size (y) = %d\n", infomap->size_x, infomap->size_y);
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

void put_xpm_img_to_test(t_game *game) // does not work with small windows
{
	game = (t_game *)game;
	mlx_put_image_to_window(game->mlx, game->wdw, game->no_texture->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->wdw, game->so_texture->img, 60, 60);
	mlx_put_image_to_window(game->mlx, game->wdw, game->ea_texture->img, 120, 120);
	mlx_put_image_to_window(game->mlx, game->wdw, game->we_texture->img, 180, 180);
}

void	reproduce_texture(t_game *game, int img_index)
{
	int			x;
	int			y;
	int			color;

	y = 240;
	while (y < 300)
	{
		x = 240;
		while (x < 300)
		{
			color = (int)get_color_in_texture(game->no_texture, x - 240, y - 240);
			mlx_pixel_put_to_img(game->imgs_set[img_index], x, y, color);
			x++;
		}
		y++;
	}
	y = 300;
	while (y < 360)
	{
		x = 300;
		while (x < 360)
		{
			color = (int)get_color_in_texture(game->no_texture, x - 300, y - 300);
			mlx_pixel_put_to_img(game->imgs_set[img_index], x, y, color);
			x++;
		}
		y++;
	}
}

// typedef struct s_game
// {
// 	t_img			**imgs_set;
// 	t_infomap			*infomap;
// 	void				*mlx;
// 	int					wdw_x;
// 	int					wdw_y;
// 	void				*wdw;
// 	int					col_ceil;
// 	int					col_floor;
// 	t_img			*no_texture;
// 	t_img			*so_texture;
// 	t_img			*ea_texture;
// 	t_img			*we_texture;
// 	bool				*keys;
// 	bool				run;
// 	struct s_player		*ply;
// 	struct s_minimap	*minimap;
// }				t_game;


void	print_ptns(t_game *game)
{
	printf("game = %p\n", game);
	printf("infomap = %p\n", game->infomap);
	printf("mlx ptn = %p\n", game->mlx);
	printf("wdw ptn = %p\n", game->wdw);
	printf("N txt = %p\n", game->no_texture);
	printf("S txt = %p\n", game->so_texture);
	printf("E txt = %p\n", game->ea_texture);
	printf("W txt = %p\n", game->we_texture);
	printf("bools = %p\n", game->keys);
	printf("img set = %p\n", game->imgs_set);	
}

void	track_the_leaks(t_game *game)
{
	mlx_destroy_window(game->mlx, game->wdw);
	free_game(&game);
	system("leaks Cub3D");
	exit(EXIT_SUCCESS);
}