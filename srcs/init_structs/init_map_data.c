/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:42:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 18:45:05 by cjulienn         ###   ########.fr       */
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

/* check if format */

void	parse_card_points(t_map_data *map_data, char *line)
{
	
}

void	parse_up_and_down(t_map_data *map_data, char *line)
{
	
}

void	parse_infos(t_map_data *map_data)
{
	int		i;
	char	*line;

	i = 0;
	while (map_data->cub && map_data->cub[i] && map_data->nb_infos < 6)
	{
		line = map_data->cub[i];
		while (ft_isspace(line)) // create ft_isspace
			line++;
		if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
			|| !ft_strncmp("EA ", line, 3) || !ft_strncmp("WE ", line, 3))
			parse_card_points(map_data, line);
		else if (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
			parse_up_and_down(map_data, line);
		else
			; // handle wrong format of info
		map_data->nb_infos++;
		i++;
	}
}

void	init_map_data(t_map_data *map_data, char *map) // to test
{
	open_map(map, map_data);
	map_data->lines = get_all_lines(map_data->fd);
	if (!map_data->lines)
		; // handle this
	map_data->cub = ft_split(map_data->lines, '\n');
	if (!map_data->cub)
		; // handle this
	map_data->nb_infos = 0;
}
