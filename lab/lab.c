/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:28:43 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/24 17:59:01 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// prototypes 

typedef struct	s_mlx_img {
	void		*img;
	void		*mlx;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_mlx_img;

typedef struct s_game
{
	t_mlx_img	**imgs_set;
	void		*mlx;
	int			wdw_x;
	int			wdw_y;
	void		*wdw;
	int			col_ceil;
	int			col_floor;
	// just testing stuff
	int			circle_x;
	int			circle_y;
	// booleans for mlx_loop_hook
	bool		*keys;
}				t_game;

// protos

int			exit_hook(t_game **game);
int			create_trgb_color(int t, int r, int g, int b);
t_mlx_img	*init_mlx_img_struct(void *mlx, int x, int y);
void		clear_mlx_img_struct(t_mlx_img **mlx_img);
void		mlx_pixel_put_to_img(t_mlx_img *mlx_img, int x, int y, int color);
void		draw_stuff(t_game *game, int color, int index);
void		draw_circle(t_game *game, int x, int y, int index);
int			key_press_hook(int keycode, t_game *game);
int			key_release_hook(int keycode, t_game *game);
void		change_circle_params(t_game *game);


void		change_circle_params(t_game *game)
{
	if (game->keys[0] == true)
	{
		if (game->circle_y - 10 >= 0)
			game->circle_y -= 10;
	}
	else if (game->keys[1] == true)
	{
		if (game->circle_x - 10 >= 0)
			game->circle_x -= 10;
	}
	else if (game->keys[2] == true)
	{
		if (game->circle_y < 400)
			game->circle_y += 10;
	}
	else if (game->keys[3] == true)
	{
		if (game->circle_x < 400)
			game->circle_x += 10;
	}
}

/* allow to terminate window when the red cross is pressed */

int	exit_hook(t_game **game)
{	
	mlx_destroy_window((*game)->mlx, (*game)->wdw);
	free(*game);
	exit(EXIT_SUCCESS);
	return (1);
}

/* create_trgb_color use bitshift ops to convert 0 numbers
between 0 and 255 (one byte size) to an int regrouping
all those infos */

int	create_trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/* init_mlx_img_struct create a new image for the minilibx,
allocated space for the struct, then creating a window attached to 
the minilibx, then getting relevant data in order to be able to 
draw pixels with the custom function mlx_pixel_put_to_img */

t_mlx_img	*init_mlx_img_struct(void *mlx, int x, int y)
{
	t_mlx_img		*new;

	new = (t_mlx_img *)malloc(sizeof(t_mlx_img));
	if (!new)
		return (NULL);
	new->img = mlx_new_image(mlx, x, y);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel,
				&new->line_length, &new->endian);
	new->width = x;
	new->height = y;
	new->mlx = mlx;
	return (new);
}

/* clear_mlx_img_struct destroy the img and free the struct */

void	clear_mlx_img_struct(t_mlx_img **mlx_img)
{
	mlx_destroy_image((*mlx_img)->mlx, (*mlx_img)->img);
	free(*mlx_img);
	*mlx_img = NULL;
}

/* mlx_pixel_put_to_img allow to draw a pixel in the img, not to the window
The img is drawa and then is "glued" into the window */

void	mlx_pixel_put_to_img(t_mlx_img *mlx_img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= mlx_img->width || y >= mlx_img->height)
		return ;
	offset = y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8);
	dst = mlx_img->addr + offset;
	*(unsigned int*)dst = color;
}

/* render landscape is used to draw floor and ceiling */

static void	render_landscape(t_game *game, int index)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->imgs_set[index]->height)
	{
		x = 0;
		while (x < game->imgs_set[index]->width)
		{
			if (y < (game->imgs_set[index]->height / 2))
			{
				mlx_pixel_put_to_img(game->imgs_set[index],
					x, y, game->col_ceil);
			}
			if (y >= (game->imgs_set[index]->height / 2))
			{
				mlx_pixel_put_to_img(game->imgs_set[index],
					x, y, game->col_floor);
			}
			x++;
		}
		y++;
	}
}

/* choose img is used to check what images should be used (index 0 or 1) 
check wether an img is used and used the other
when no img is used, we use the first image (index 0) */

static int	choose_img(t_game *game)
{
	int		img_index;

	if (game->imgs_set[0] == NULL)
		img_index = 0;
	else
		img_index = 1;
	return (img_index);
}

/* render frame render is used to rotate the set of two images.
The first img is used the first time. When player triggers a movement,
it render another frame. The images are used alternatively. 
The already existing image is destroyed after the second img is put to the 
window */

int	render_frame(t_game *game) // to debug
{
	static bool	first_iter = true;
	int			img_index;

	if (first_iter == true)
	{
		game->imgs_set[0] = init_mlx_img_struct(game->mlx,
			400, 400);
		render_landscape(game, 0);
		draw_circle(game, game->circle_x, game->circle_y, 0);
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[0]->img, 0, 0);
		first_iter = false;
		return (0);
	}
	img_index = choose_img(game);
	game->imgs_set[img_index] = init_mlx_img_struct(game->mlx,
	400, 400);
	render_landscape(game, img_index);
	if (game->keys[0] == true || game->keys[1] == true || game->keys[2] == true || game->keys[3] == true)
		change_circle_params(game);
	draw_circle(game, game->circle_x, game->circle_y, img_index);
	if (img_index == 0)
	{
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[0]->img, 0, 0);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->wdw,
			game->imgs_set[1]->img, 0, 0);
	}	
	if (img_index == 0) // pb there
		clear_mlx_img_struct(&game->imgs_set[1]);
	if (img_index == 1)
		clear_mlx_img_struct(&game->imgs_set[0]);
	return (0);
}

static int	check_distance(int x, int y, int i, int j)
{
	double	radius = 20.0;
	double	distance;
	double	tol = 3.00;

	distance = sqrt(pow((i - x), 2.0) + pow((j - y), 2.0));
	if (distance >= (radius - tol) && distance <= (radius + tol))
		return (1);
	return (0);
}

void	draw_circle(t_game *game, int x, int y, int index)
{
	int		i = 0;
	int		j = 0;

	while (j < game->wdw_y)
	{
		i = 0;
		while (i < game->wdw_x)
		{
			if (check_distance(x, y, i, j) == 1)
				mlx_pixel_put_to_img(game->imgs_set[index], i, j, 0x00000);
			i++;
		}
		j++;
	}
}

int	key_press_hook(int keycode, t_game *game) // change game
{
	printf("keycode = %d\n", keycode);
	if (keycode == 13) // UP
		game->keys[0] = true;
	else if (keycode == 1) // DOWN
		game->keys[2] = true;
	else if (keycode == 2) // RIGHT
		game->keys[3] = true;
	else if (keycode == 0) // LEFT
		game->keys[1] = true;
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == 13) // UP
		game->keys[0] = false;
	else if (keycode == 1) // DOWN
		game->keys[2] = false;
	else if (keycode == 2) // RIGHT
		game->keys[3] = false;
	else if (keycode == 0) // LEFT
		game->keys[1] = false;
	return (0);
}

int main(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (1);
	game->mlx = mlx_init(); // init mlx
	game->wdw = mlx_new_window(game->mlx, 400, 400, "tester");
	game->imgs_set = (t_mlx_img **)malloc(sizeof(t_mlx_img *) * 2);
	if (!game->imgs_set)
		exit(EXIT_FAILURE);
	game->imgs_set[0] = NULL;
	game->imgs_set[1] = NULL;
	game->wdw_x = 400;
	game->wdw_y = 400;
	game->col_ceil =  0x00FF0000;
	game->col_floor = 0x00FFFF;
	game->circle_x = 199;
	game->circle_y = 199;
	game->keys = (bool *)malloc(sizeof(bool) * 4);
	if (!game->keys)
		return (1);
	for (int i = 0; i < 4;i++)
		game->keys[i] = false;
	mlx_hook(game->wdw, 17, 0, exit_hook, &game); // X button
	mlx_hook(game->wdw, 2, 0, key_press_hook, game); // change booleans when keys are pressed
	mlx_hook(game->wdw, 3, 0, key_release_hook, game); // change booleans when keys are released
	mlx_loop_hook(game->mlx, render_frame, game); // render every frame
	mlx_loop(game->mlx);
	return (0);
}
