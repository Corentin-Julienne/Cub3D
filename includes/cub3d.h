/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/13 12:56:27 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
#include <stdio.h> // printf to test

# include "../libft/libft.h"

# define NB_ARG_ERR		"Error: wrong number of arguments\nUsage : ./Cub3D [map with .ber extension]\n"
# define CUB_MAP_ERR	"Error: map in cub format does not exists. Please provide a viable path\n"

typedef struct s_map_data
{
	char			*lines;
	char			**cub;
	char			**map;
	char			**map_ext;
	int				fd;
	int				size_x;
	int				size_y;
	int				nb_infos;
	char			*no_text;
	char			*so_text;
	char			*ea_text;
	char			*we_text;
	int				*floor_col;
	int				*ceil_col;
}				t_map_data;

/* CHECK_MAP */

/* ERRORS */

/* err_msgs.c */
void		print_err_msg(char *msg);

/* INIT STRUCTS */

/* init_map_data.c */
void		init_map_data(t_map_data *map_data, char *map);

/* PARSING */

/* parse_infos.c */
void		parse_infos(t_map_data *map_data);
/* parse_map.c */
void		parse_map(t_map_data *map_data, int i);

/* MAIN */

#endif