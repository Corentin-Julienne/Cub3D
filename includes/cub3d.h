/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 10:09:10 by mpeharpr         ###   ########.fr       */
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
# include <stdio.h>

# include "../libft/libft.h"

/* MACROS FOR ERRORS MSGS */

/* wrong number of arguments (argc != 2) */
# define ERR_NB_ARGS		"Wrong number of arguments\n \
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
/* mlx init err */
# define ERR_MLX			"Mlx init failure\n"
/* problem with ray calculation */
# define ERR_RAY  			"The ray has been out of the map\n"
/* problem with unexistant texture path */
# define ERR_TXT_PATH		"Texture is not in .xpm format or invalid path\n"

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

/* MACROS FOR WASD KEY AND DIRECTIONNAL ARROW AND MOUSE BUTTTONS */

# define W_KEY				13
# define A_KEY				1
# define S_KEY				2
# define D_KEY				0
# define LEFT_ARROW			123
# define RIGHT_ARROW		124
# define SHIFT_KEY			257
# define ESCAPE				53
# define SCROLL_UP			4
# define SCROLL_DOWN		5

/* MACROS FOR HOOKS AND EVENTS */

# define EXIT_HOOK			17
# define KEY_PRESS_HOOK		2
# define KEY_RELEASE_HOOK	3

/* MACROS FOR GAME SETTINGS */

# define CUBES_SIZE			64
# define PLY_VIEW_FOV_DEG	60

/* MACROS FOR IMG CREATION */

# define NEW_IMG			1
# define IMPORT				2

typedef struct s_infomap
{
	char				*lines;
	char				**cub;
	char				**map;
	int					fd;
	int					size_x;
	int					size_y;
	int					nb_infos;
	char				*no_text;
	char				*so_text;
	char				*ea_text;
	char				*we_text;
	int					*floor_col;
	int					*ceil_col;
}				t_infomap;

typedef struct s_img
{
	void				*img;
	void				*mlx;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}				t_img;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				ang_y;
	double				dist_from_proj;
	struct s_game		*game;
}				t_player;

typedef struct s_ray
{
	char				**map;
	int					size_x;
	int					size_y;
	double				ang;
	double				rad;
	double				start_x;
	double				start_y;
	int					cur_map_x;
	int					cur_map_y;
	double				**found_vert;
	double				**found_horiz;
	double				**order;
	struct s_game		*game;
}				t_ray;

typedef struct s_raysult
{
	double				dist;
	double				offset;
	char				wall_orientation;
}				t_raysult;

typedef struct s_minimap
{
	int					width;
	int					height;
	int					offset;
	int					padding_x;
	int					padding_y;
	int					img_index;
	int					edge_len;
	int					col_back;
	int					col_square;
	int					col_ply;
}				t_minimap;

typedef struct s_game
{
	t_img				**imgs_set;
	t_infomap			*infomap;
	void				*mlx;
	int					wdw_x;
	int					wdw_y;
	void				*wdw;
	int					col_ceil;
	int					col_floor;
	t_img				*no_texture;
	t_img				*so_texture;
	t_img				*ea_texture;
	t_img				*we_texture;
	bool				*keys;
	bool				run;
	struct s_player		*ply;
	struct s_minimap	*minimap;
}				t_game;

/* ALGORITHM */

/* algorithm.c */
void		send_raycast(t_game *game, double ray_ang, t_raysult *res);
/* intersections.c */
void		find_vert_inter(t_ray *ray);
void		find_horiz_inter(t_ray *ray);
void		calc_wall_orientation(t_ray *ray, t_raysult *res, int i);
/* filter.c */
void		create_inter_array(t_ray *ray);
/* allocationc.c */
void		alloc_ray_intersections(t_ray *ray);

/* BONUS */

/* crosshair.c */
void		render_crosshair(t_game *game, int img_index);
/* minimap_utils.c */
int			is_within_minimap(t_minimap *mini, int x, int y);
int			is_map_fitting(t_minimap *mini, t_game *game);
void		render_square(t_minimap *mini, t_game *game, int x, int y);
void		render_background(t_minimap *mini, t_game *game, int img_index);
/* minimap.c */
void		render_minimap(t_minimap *mini, t_game *game, int img_index);
void		init_minimap_struct(t_game *game);

/* FREE */

/* free_game.c*/
void		free_map(t_infomap **infomap);
void		free_game(t_game **game);
/* free_raycast.c */
void		free_ray_when_problem(t_ray *ray, char *spec);
void		free_ray_intersections(t_ray *ray);
/* free_utils.c */
void		free_and_nullify(void **to_free);
void		free_problem_str_arr(char ***split, int i);
void		free_split(char ***split);
void		clear_mlx_img_struct(t_img **mlx_img);

/* GAME */

/* init_game.c */
void		init_game(t_game *game);
/* init_game_struct.c */
t_game		*init_game_struct(t_infomap *infomap);
/* init_player.c */
void		init_player(t_game *game);
/* update_player.c */
int			update_player_data(t_game *game, t_player *ply);

/* GRAPHICS */

/* colors.c */
void		get_colors(t_game *game);
/* draw.c */
void		mlx_pixel_put_to_img(t_img *mlx_img, int x, int y, int color);
int			get_color_in_texture(t_img *mlx_img, int x, int y);
/* init_img_struct.c */
t_img		*init_img_struct(void *mlx, int x, int y, int type);
/* render_frame.c */
int			render_frame(t_game *game);
/* render_algo.c */
void		render_walls(t_game *game, int img_index, double start_ang, int x);

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
void		print_err_msg(char *msg);
void		err_msg_and_free_map(char *spec, t_infomap *infomap);
void		err_msg_and_free_all(char *spec, t_game *game);
/* math.c */
double		ceil_double(double nb);
double		calc_dist(double x1, double y1, double x2, double y2);
/* parsing_tools.c */
int			is_texture_path_valid(char *path);
void		convert_to_intarr(t_infomap *infomap,
				char *line, char **color_arr);
/* textures.c */
void		get_texts_north_south(t_game *game, t_infomap *infomap);
void		get_texts_west_east(t_game *game, t_infomap *infomap);

#endif
