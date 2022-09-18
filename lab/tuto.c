/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:28:48 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/18 13:37:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

/* create_trgb_color use bitshift ops to convert 0 numbers
between 0 and 255 (one byte size) to an int regrouping
all thos infos */

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

void	clear_mlx_img_struct(t_mlx_img *mlx_img)
{
	mlx_destroy_image(mlx_img->mlx, mlx_img->img);
	free(mlx_img);
	mlx_img = NULL;
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

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_mlx_img	*frame;

	mlx = mlx_init(); // init mlx
	
	mlx_win = mlx_new_window(mlx, 400, 400, "Hello world!");
	frame = init_mlx_img_struct(mlx, 400, 400);
	if (!frame)
		printf("couille !!!\n");
		
	int i = 0;
	while (i < 800)
	{
		mlx_pixel_put_to_img(frame, i, i, 0x00FF0000);
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, frame->img, 0, 0);
	mlx_loop(mlx);
}
