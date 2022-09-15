/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:39 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/15 14:49:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* parse_card_points is used to retrieve the paths to the textures
of north, south, east and west walls. In case of error in format or 
duplicated param it triggers a relevant error message. Otherwise,
it store the differents paths in map_data for forther usage */

static void	parse_card_points(t_map_data *map_data, char *line) // to test
{
	char	*path;

	line = line + 3;
	if (!line[0])
		err_msg_and_free(ERR_PARAM_FORMAT, map_data);
	path = ft_strtrim(line, " \t\v\f\r");
	if (!path)
		err_msg_and_free(ERR_MALLOC, map_data);
	if (ft_strchr(path, ' ') || ft_strchr(path, '	'))
		err_msg_and_free(ERR_PARAM_FORMAT, map_data);
	if (!ft_strncmp("NO ", line, 3) && !map_data->no_text)
		map_data->no_text = path;
	else if (!ft_strncmp("SO ", line, 3) && !map_data->so_text)
		map_data->so_text = path;
	else if (!ft_strncmp("EA ", line , 3) && !map_data->ea_text)
		map_data->ea_text = path;
	else if (!ft_strncmp("WE ", line, 3) && !map_data->we_text)
		map_data->we_text = path;
	else
		err_msg_and_free(ERR_DUP_PARAM, map_data);
}

/* store_intarr_to_struct store the int* containing RGB info
for ceiling or floor to the relevant map_data category.
If information is duplicated, triggers an error msg */

static void	store_intarr_to_struct(t_map_data *map_data, char *line,
				int *colors, char **color_arr) // to test
{
	if (!ft_strncmp("C ", line, 2) && map_data->ceil_col == NULL)
		map_data->ceil_col = colors;
	else if (!ft_strncmp("F ", line, 2) && map_data->floor_col == NULL)
		map_data->floor_col = colors;
	else
	{
		free_split(color_arr);
		free(colors);
		err_msg_and_free(ERR_DUP_PARAM, map_data);
	}
	free_split(color_arr);
}

/* convert_to_intarr convert a char** to an int[3] which
contains colors for ceiling or floor in a RGB format
trigger an err msg if the format is out of range 0 - 255 */

static void	convert_to_intarr(t_map_data *map_data, char *line,
				char **color_arr) // to test
{
	int		*colors;
	int		i;

	colors = (int *)malloc(sizeof(int) * 3);
	if (!colors)
		err_msg_and_free(ERR_MALLOC, map_data);
	i = 0;
	while (i < 3)
	{
		if (ft_strlen(color_arr[i]) > 3)
		{
			free_split(color_arr);
			free(colors);
			err_msg_and_free(ERR_COLOR_RANGE, map_data);
		}
		colors[i] = ft_atoi(color_arr[i]);
		if (colors[i] > 255 || colors[i] < 0)
		{
			free_split(color_arr);
			free(colors);
			err_msg_and_free(ERR_COLOR_RANGE, map_data);
		}
		i++;
	}
	store_intarr_to_struct(map_data, line, colors, color_arr);
}

/* parse_up_and_down retrieve info for colors of ceiling and floor 
check for potential errors in format, and triggers error msgs
if it is the case. transform the data read on the map to an array of strings
which will be transformed into an array of three ints by the function
convert_to_intarr*/

static void	parse_up_and_down(t_map_data *map_data, char *line) // to test
{
	char	**color_arr;
	char	*info;
	int		i;

	line = line + 3;
	if (!line[0])
		err_msg_and_free(ERR_PARAM_FORMAT, map_data);
	info = ft_strtrim(line, " \t\v\f\r");
	if (!info)
		err_msg_and_free(ERR_MALLOC, map_data);
	i = 0;
	while (line && line[i])
	{
		if (line[i] != ',' && ft_isdigit(line[i]) == 0)
		{
			free(info);
			err_msg_and_free(ERR_COLOR_FORMAT, map_data);
		}
		i++;
	}
	color_arr = ft_split(info, ',');
	free(info);
	if (!color_arr)
		err_msg_and_free(ERR_MALLOC, map_data);
	convert_to_intarr(map_data, line, color_arr);
}

/* parse_infos is used to retrieve and store in map_data
every useful information such as ceiling and floor color
paths of south, north, east and west textures and the map itself
triggers exit message in case of problem
(including duplicate params, missing params and wrong format params) */

void	parse_infos(t_map_data *map_data) // to test
{
	int		i;
	char	*line;

	i = 0;
	while (map_data->cub && map_data->cub[i] && map_data->nb_infos < 6)
	{
		line = map_data->cub[i];
		while (ft_isspace(line[0]))
			line++;
		if (ft_strlen(line) >= 3 && (!ft_strncmp("NO ", line, 3)
			|| !ft_strncmp("SO ", line, 3) || !ft_strncmp("EA ", line, 3)
			|| !ft_strncmp("WE ", line, 3)))
			parse_card_points(map_data, line);
		else if ( ft_strlen(line) >= 3 &&
			(!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)))
			parse_up_and_down(map_data, line);
		else
			err_msg_and_free(ERR_PARAM_FORMAT, map_data);
		map_data->nb_infos++;
		i++;
	}
	if (map_data->nb_infos != 6)
		err_msg_and_free(ERR_PARAM_NB, map_data);
	parse_map(map_data, i);
}
