/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infomap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:42:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/16 13:18:50 by cjulienn         ###   ########.fr       */
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
store the openned map in map->fd */

static void	open_map(char *map, t_infomap *infomap)
{
	infomap->fd = open(map, O_RDONLY);
	if (infomap->fd == -1)
		err_msg_and_free_map(ERR_PATH_MAP, infomap);
	if (!is_format_cub(map))
	{
		close(infomap->fd);
		err_msg_and_free_map(ERR_NOT_CUB, infomap);
	}
}

/* get_all_lines use get_next_line and join every line together,
then returns it. returns NULL when encountering memory allocation problem */

static char	*get_all_lines(int fd)
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

/* init_infomap assign NULL to every arg of the struct in order to avoid
segfault when trying to free the struct and its elements
Then, retrieve map info in a single string (map->lines),
split it into a char** (map->cub), and will extract from it  
the relevant infos (colors of floor and ceiling, texture paths), 
and the extrat the map itself in map->map */

void	init_infomap_struct(t_infomap *infomap, char *map)
{
	infomap->lines = NULL;
	infomap->cub = NULL;
	infomap->map = NULL;
	infomap->no_text = NULL;
	infomap->so_text = NULL;
	infomap->ea_text = NULL;
	infomap->we_text = NULL;
	infomap->ceil_col = NULL;
	infomap->floor_col = NULL;
	open_map(map, infomap);
	infomap->lines = get_all_lines(infomap->fd);
	close(infomap->fd);
	if (!infomap->lines)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	infomap->cub = ft_split(infomap->lines, '\n');
	if (!infomap->cub)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	infomap->nb_infos = 0;
	parse_infos(infomap);
}
