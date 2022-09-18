/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:28:43 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/18 11:37:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	void		*mlx;
	void		*wdw;
	int			wdw_x;
	int			wdw_y;	
}				t_data;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_img;

// utils 

static void	mlx_pixel_put_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->size_line) + (x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int*)dst = color;
}


static int	exit_hook(t_data **data)
{	
	mlx_destroy_window((*data)->mlx, (*data)->wdw);
	free(*data);
	exit(EXIT_SUCCESS);
	return (1);
}

int main(void)
{
	t_data			*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->mlx = mlx_init();
	data->wdw_x = 800;
	data->wdw_y = 640;
	data->wdw = mlx_new_window(data->mlx, data->wdw_x, data->wdw_y, "Lab");

	t_img			*img_test;

	img_test = (t_img *)malloc(sizeof(t_img));
	if (!img_test)
		return (1);
	img_test->img = mlx_new_image(data->mlx, 800, 640); // create new image
	img_test->addr = mlx_get_data_addr(img_test->img, &img_test->bits_per_pixel,
						&img_test->size_line, &img_test->endian);
	printf("new img = addr : |%p|, bits_per_pixel : |%d|, size_line : |%d| and endian : |%d|\n",
				img_test->addr, img_test->bits_per_pixel, img_test->size_line, img_test->endian);
	
	// putting directly pixels to window
	
	int		x = 0;
	while (x < 200)
	{
		mlx_pixel_put(data->mlx, data->wdw, x, 400, 0x00FF8070);
		x++;
	}
	int 	y = 0;
	while (y < 200)
	{
		mlx_pixel_put_to_img(img_test->img, y, 400, 0x00FF8070);
		y++;
	}
	printf("go till there\n");
	mlx_put_image_to_window(data->mlx, data->wdw, img_test->img, 0, 0);
	mlx_hook(data->wdw, 17, 0, exit_hook, &data); // allow pressing X to quit program
	mlx_loop(data->mlx); // trigger program activation
	return (0);
}
