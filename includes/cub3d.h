/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/10 16:17:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
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
# define ERR_PSP			"The number of player starting position is not equal \
to one\n"
/* invalid char in map grid */
# define ERR_INVALID_CHAR	"Invalid character in map grid\n"
/* empty line within map grid */
# define ERR_EMPTY_LINE		"Empty line within map grid or duplicated \
and/or uncorrectly formated infos\n"
/* generic for malloc error*/
# define ERR_MALLOC			"Memory allocation failure\n"

/* MACROS FOR WINDOW SIZE */

# define WDW_WIDTH			1366
# define WDW_HEIGHT			768

/* MACROS FOR CONVERTING TRGB TO INT */

# define CEILING			1
# define FLOOR				2

/* MACROS FOR PLAYER STARTING ORIENTATION */

# define NORTH				1
# define SOUTH				2
# define EAST				3
# define WEST				4

/* MACROS FOR WASD KEY AND DIRECTIONNAL ARROW */

# define W_KEY				13
# define A_KEY				1
# define S_KEY				2
# define D_KEY				0
# define LEFT_ARROW			123
# define RIGHT_ARROW		124
# define ESCAPE				53

/* MACROS FOR HOOKS AND EVENTS */

# define EXIT_HOOK			17
# define KEY_PRESS_HOOK		2
# define KEY_RELEASE_HOOK	3

/* MACROS FOR GAME SETTINGS */

# define WALL_HEIGHT		64
# define CUBES_SIZE			64
# define PLY_VIEW_HEIGHT	32
# define PLY_VIEW_FOV_DEG	60

typedef struct s_infomap
{
	char		*lines;
	char		**cub;
	char		**map;
	int			fd;
	int			size_x;
	int			size_y;
	int			nb_infos;
	char		*no_text;
	char		*so_text;
	char		*ea_text;
	char		*we_text;
	int			*floor_col;
	int			*ceil_col;
	int			direction;
}				t_infomap;

typedef struct	s_mlx_img 
{
	void		*img;
	void		*mlx;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_mlx_img;

typedef struct s_texture
{
	void		*img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_game
{
	t_mlx_img		**imgs_set;
	t_infomap		*infomap;
	void			*mlx;
	int				wdw_x;
	int				wdw_y;
	void			*wdw;
	int				col_ceil;
	int				col_floor;
	t_texture		*no_texture;
	t_texture		*so_texture;
	t_texture		*ea_texture;
	t_texture		*we_texture;
	bool			*keys;
	int				ray_offset_ang;
	struct s_player	*player;
}				t_game;

typedef struct s_player {
	double		pos_x;
	double		pos_y;
	double		ang_y; // Rotation of the camera horizontally
	double		dist_from_proj; // Distance between the viewer and the projection screen
	t_game		*game;
}				t_player;

typedef struct	s_raycast {
	double		**intersections_x;
	int			inter_x_size;
	double		**intersections_y;
	int			inter_y_size;
	double		wall_touch_x;
	double		wall_touch_y;
}				t_raycast;

/* ALGORITHM */

/* algorithm.c */
void    	raycast(t_game *game, t_raycast *cast, double ang_offset);
/* distances.c */
double		calc_dist(double x1, double y1, double x2, double y2);

/* BONUS */

/* crosshair.c */
void		render_crosshair(t_game *game, int img_index);

/* GAME */

/* init_game.c */
void		init_game(t_game *game);
/* init_game_struct.c */
t_game		*init_game_struct(t_infomap *infomap);
/* init_player.c */
void    	init_player(t_game *game);

/* GRAPHICS */

/* colors.c */
void		get_colors(t_game *game);
/* draw.c */
void		mlx_pixel_put_to_img(t_mlx_img *mlx_img, int x, int y, int color);
/* init_mlx_img_struct.c */
t_mlx_img	*init_mlx_img_struct(void *mlx, int x, int y);
void		clear_mlx_img_struct(t_mlx_img **mlx_img);
/* render_frame.c */
int			render_frame(t_game *game);
/* render_algo.c */
void    	render_everything(t_game *game, int img_index);

/* PARSING */

/* init_infomap.c */
void		init_infomap_struct(t_infomap *infomap, char *map);
/* map_validity.c */
void		check_map_validity(t_infomap *infomap);
/* parse_infos.c */
void		parse_infos(t_infomap *infomap);
/* parse_map.c */
void		parse_map(t_infomap *infomap, int i);

/* UTILS */

/* err_msgs.c */
void		err_msg_and_free(char *spec, t_infomap *infomap);
void		err_msg_and_free_all(char *spec, t_game *game);
void		print_err_msg(char *msg);
/* free.c */
void		free_and_nullify(void **to_free);
void		free_map(t_infomap *infomap);
void		free_problem_str_arr(char **split, int i);
void		free_split(char **split);
/* math.c */
double  	ceil_double(double nb);


// -----------------------------------------//
// debug [to kill before pushing to vogsphere]

void		print_infomap_infos(t_infomap *infomap);
void		print_infos(t_infomap *infomap);
void		print_oneline(t_infomap *infomap);
void		leaks_killing(void);
void		print_cub_file(t_infomap *infomap);
void 		print_split(char **split);
void 		put_xpm_img_to_test(t_game *game);

#endif
