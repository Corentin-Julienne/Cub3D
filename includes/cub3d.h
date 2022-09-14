/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 18:18:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
#include <stdio.h> // printf to test [supress before pushing to vogsphere]

# include "../libft/libft.h"

/* MACROS FOR ERRORS MSGS */

/* wrong number of arguments (argc != 2) */
# define NB_ARG_ERR		"Wrong number of arguments\nUsage : ./Cub3D [map with .ber extension]\n"
/* map not in format .cub */
# define CUB_MAP_ERR	"Map in cub format does not exists. Please provide a viable path\n"
/* valid arguments in the map but wrong format */
# define FORMAT_MAP_ERR	"One or several parameters provided in map are in a wrong format\n"
/* missign parameter in the map */
# define NB_PARAMS_ERR	"One or several parameters are missing in the map\n"
/* generic for malloc error*/
# define MALLOC_ERR		"Memory allocation failure\n"

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
}				t_map_data;

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

#endif
