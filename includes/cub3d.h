/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:28:01 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 11:14:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>

# include "../libft/libft.h"

# define NB_ARG_ERR				"Error: wrong number of arguments\nUsage : ./Cub3D [map with .ber extension]\n"

typedef struct s_map_data
{
	char			**cub;
	char			**map;
	char			**map_ext;
	int				size_x;
	int				size_y;
}				t_map_data;

/* check_map */
/* errors */
void		print_err_msg(const char *msg);
/* init_structs */
void		init_map_data(t_map_data *map_data, char *map);
/* main */

#endif
