/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/15 16:13:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
#include <stdio.h> // printf to test [supress before pushing to vogsphere]

# include "../libft/libft.h"

/* MACROS FOR ERRORS MSGS */

/* wrong number of arguments (argc != 2) */
# define ERR_NB_ARGS		"Wrong number of arguments\n\
Usage : ./Cub3D [map with .ber extension]\n"
/* map not in format .cub */
# define ERR_NOT_CUB		"The map provided is not in .cub format\n"
/* the path to the map provided by the user is invalid */
# define ERR_PATH_MAP		"Map does not exist or is unreadable. \
Please provide a viable path\n"
/* valid arguments in the map but wrong format */
# define ERR_PARAM_FORMAT	"One or several parameters provided \
by the map are in a wrong format\n"
/* missign parameter in the map */
# define ERR_PARAM_NB		"One or several parameters are missing in the map\n"
/* duplicated params */
# define ERR_DUP_PARAM		"One or several parameters have been duplicated \
in the map\n"
/* color of ceiling or floor are in a wrong format */
# define ERR_COLOR_FORMAT	"RGB colors are in a wrong format\n"
/* color of ceiling or floor are outside range (0 - 255) */
# define ERR_COLOR_RANGE	"RGB colors outside of range 0 - 255\n"
/* no map  grid is present */
# define ERR_MISSING_GRID	"Map grid is not present in the map\n"
/* map is not surrounded by walls */
# define ERR_BREACH_MAP		"Map is not surrounded by walls\n"
/* lack or several player starting position */
# define ERR_PSP			"The number player starting position is not equal \
to one\n"
/* invalid char in map grid */
# define ERR_INVALID_CHAR	"Invalid character in map grid\n"
/* empty line within map grid */
# define ERR_EMPTY_LINE		"Empty line within map grid\n"
/* generic for malloc error*/
# define ERR_MALLOC			"Memory allocation failure\n"

typedef struct s_map_data
{
	char			*lines;
	char			**cub;
	char			**map;
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
}					t_map_data;

/* CHECK_MAP */

/* map_validity.c */
void		check_map_validity(t_map_data *map_data);

/* INIT STRUCTS */

/* init_map_data.c */
void		init_map_data(t_map_data *map_data, char *map);

/* PARSING */

/* parse_infos.c */
void		parse_infos(t_map_data *map_data);
/* parse_map.c */
void		parse_map(t_map_data *map_data, int i);

/* MAIN */

/* UTILS */

/* err_msgs.c */
void		err_msg_and_free(char *spec, t_map_data *map_data);
void		print_err_msg(char *msg);
/* free.c */
void		free_and_nullify(void **to_free);
void		free_map_data(t_map_data *map_data);
void		free_problem_str_arr(char **split, int i);
void		free_split(char **split);

// debug [to kill before pushing to vogsphere]

void		print_map_infos(t_map_data *map_data);
void		leaks_killing(void);

#endif
