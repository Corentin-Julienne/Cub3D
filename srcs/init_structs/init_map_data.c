/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:42:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/13 12:51:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* get_y_size allow to check the size of the y-axis of the map */

// static size_t	get_y_size(char	**map)
// {
// 	size_t		y_size;

// 	y_size = 0;
// 	while (map && map[y_size])
// 		y_size++;
// 	return (y_size);
// }

static void	open_map(char *map, t_map_data *map_data) // to test
{
	map_data->fd = open(map, O_RDONLY);
	if (map_data->fd == -1)
	{
		free(map_data);
		map_data = NULL;
		print_err_msg(CUB_MAP_ERR);
	}
}

static char	*get_all_lines(int fd) // to test
{
	char	*next_line;
	char	*all_lines;
	char	*tmp;
	int		iter;

	next_line = NULL;
	all_lines = ft_strdup("");
	if (!all_lines)
		return (NULL);
	iter = 0;
	while (42)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		tmp = ft_strjoin(all_lines, next_line);
		if (!tmp)
			return (NULL);
		free(all_lines);
		all_lines = tmp;
		free(next_line);
		next_line = NULL;
		iter++;
	}
	return (all_lines);
}

void	init_map_data(t_map_data *map_data, char *map) // to test
{
	open_map(map, map_data);
	map_data->lines = get_all_lines(map_data->fd);
	close(map_data->fd);
	if (!map_data->lines)
		; // handle this
	map_data->cub = ft_split(map_data->lines, '\n');
	if (!map_data->cub)
		; // handle this
	map_data->nb_infos = 0;
	map_data->no_text = NULL;
	map_data->so_text = NULL;
	map_data->ea_text = NULL;
	map_data->we_text = NULL;
	map_data->ceil_col = NULL;
	map_data->floor_col = NULL;
	parse_infos(map_data);
}
