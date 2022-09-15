/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:42:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/15 14:40:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check wether the map provided is in .cub format
return 1 if it is the case, 0 otherwise */

static int	is_format_cub(char *map)
{
	int		length;

	length = ft_strlen(map);
	if (length < 5 || ft_strncmp(map + (length - 4), ".cub", 4) != 0)
		return (0);
	return (1);
}

/* open the map, check wether the map in in .cub format,
trigger an error if it is not the case,
or if the path provided does not exist. If everything goes well,
store the openned map in map_data->fd */

static void	open_map(char *map, t_map_data *map_data) // to test
{
	map_data->fd = open(map, O_RDONLY);
	if (map_data->fd == -1)
		err_msg_and_free(ERR_PATH_MAP, map_data);
	if (!is_format_cub(map))
	{
		close(map_data->fd);
		err_msg_and_free(ERR_NOT_CUB, map_data);
	}
}

/* get_all_lines use get_next_line and join every line together,
then returns it. returns NULL when encountering memory allocation problem */

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

/* init_map_data assign NULL to every arg of the struct in order to avoid
segfault when trying to free the struct and its elements
Then, retrieve map info in a single string (map_data->lines),
split it into a char** (map_data->cub), and will extract from it  
the relevant infos (colors of floor and ceiling, texture paths), 
and the extrat the map itself in map_data->map */

void	init_map_data(t_map_data *map_data, char *map) // to test
{
	map_data->lines = NULL;
	map_data->cub = NULL;
	map_data->map = NULL;
	map_data->no_text = NULL;
	map_data->so_text = NULL;
	map_data->ea_text = NULL;
	map_data->we_text = NULL;
	map_data->ceil_col = NULL;
	map_data->floor_col = NULL;
	open_map(map, map_data);
	map_data->lines = get_all_lines(map_data->fd);
	close(map_data->fd);
	if (!map_data->lines)
		err_msg_and_free(ERR_MALLOC, map_data);
	map_data->cub = ft_split(map_data->lines, '\n');
	if (!map_data->cub)
		err_msg_and_free(ERR_MALLOC, map_data);
	map_data->nb_infos = 0;
	parse_infos(map_data);
}
