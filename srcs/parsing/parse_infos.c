/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:39 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 12:37:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* parse_card_points is used to retrieve the paths to the textures
of north, south, east and west walls. In case of error in format or 
duplicated param it triggers a relevant error message. Otherwise,
it store the differents paths in map for forther usage */

static int	store_card_points(t_infomap *infomap, char *path, char *cpy)
{
	if (!ft_strncmp("NO ", cpy, 3) && !infomap->no_text)
	{
		infomap->no_text = path;
		return (0);
	}
	else if (!ft_strncmp("SO ", cpy, 3) && !infomap->so_text)
	{
		infomap->so_text = path;
		return (0);
	}
	else if (!ft_strncmp("EA ", cpy, 3) && !infomap->ea_text)
	{
		infomap->ea_text = path;
		return (0);
	}
	else if (!ft_strncmp("WE ", cpy, 3) && !infomap->we_text)
	{
		infomap->we_text = path;
		return (0);
	}
	return (1);
}

static void	parse_card_points(t_infomap *infomap, char *line)
{
	char	*path;
	char	*cpy;

	cpy = line;
	line = line + 3;
	if (!line[0])
		err_msg_and_free_map(ERR_PARAM_FORMAT, infomap);
	path = ft_strtrim(line, " 	");
	if (!path)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	if (ft_strchr(path, ' ') || ft_strchr(path, '	'))
	{
		free(path);
		err_msg_and_free_map(ERR_PARAM_FORMAT, infomap);
	}
	if (store_card_points(infomap, path, cpy) == 1)
	{
		free(path);
		err_msg_and_free_map(ERR_DUP_PARAM, infomap);
	}
}

/* parse_up_and_down retrieve info for colors of ceiling and floor 
check for potential errors in format, and triggers error msgs
if it is the case. transform the data read on the map to an array of strings
which will be transformed into an array of three ints by the function
convert_to_intarr*/

static void	parse_up_and_down(t_infomap *infomap, char *line)
{
	char	**color_arr;
	char	*info;
	int		i;

	line = line + 2;
	if (!line[0])
		err_msg_and_free_map(ERR_PARAM_FORMAT, infomap);
	info = ft_strtrim(line, "	 ");
	if (!info)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	i = 0;
	while (info && info[i])
	{
		if (info[i] != ',' && ft_isdigit(info[i]) == 0)
		{
			free(info);
			err_msg_and_free_map(ERR_COLOR_FORMAT, infomap);
		}
		i++;
	}
	color_arr = ft_split(info, ',');
	free(info);
	if (!color_arr)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	convert_to_intarr(infomap, line - 2, color_arr);
}

/* parse_infos is used to retrieve and store in map
every useful information such as ceiling and floor color
paths of south, north, east and west textures and the map itself
triggers exit message in case of problem
(including duplicate params, missing params and wrong format params) */

void	parse_infos(t_infomap *infomap)
{
	int		i;
	char	*line;

	i = 0;
	while (infomap->cub && infomap->cub[i] && infomap->nb_infos < 6)
	{
		line = infomap->cub[i];
		while (ft_isspace(line[0]))
			line++;
		if (ft_strlen(line) >= 3 && (!ft_strncmp("NO ", line, 3)
				|| !ft_strncmp("SO ", line, 3) || !ft_strncmp("EA ", line, 3)
				|| !ft_strncmp("WE ", line, 3)))
			parse_card_points(infomap, line);
		else if (ft_strlen(line) >= 3
			&& (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)))
			parse_up_and_down(infomap, line);
		else
			err_msg_and_free_map(ERR_PARAM_FORMAT, infomap);
		infomap->nb_infos++;
		i++;
	}
	if (infomap->nb_infos != 6)
		err_msg_and_free_map(ERR_PARAM_NB, infomap);
	parse_map(infomap, i);
}
