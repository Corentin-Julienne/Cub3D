/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:39 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 17:56:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_card_points(t_map_data *map_data, char *line)
{
	char	*path;

	line = line + 3;
	if (!line[0])
		; // missing path error
	path = ft_strtrim(line, " \t\v\f\r");
	if (!path)
		err_msg_and_free(MALLOC_ERR, map_data);
	if (ft_strchr(path, ' ') || ft_strchr(path, '	'))
		; // free space within the path error
	if (!ft_strncmp("NO ", line, 3) && !map_data->no_text)
		map_data->no_text = path;
	else if (!ft_strncmp("SO ", line, 3) && !map_data->so_text)
		map_data->so_text = path;
	else if (!ft_strncmp("EA ", line , 3) && !map_data->ea_text)
		map_data->ea_text = path;
	else if (!ft_strncmp("WE ", line, 3) && !map_data->we_text)
		map_data->we_text = path;
	else
		; // err msg because relevant info has been duplicated
}

static void	convert_to_intarr(t_map_data *map_data, char *line,
				char **color_arr) // to test [MALLOC PBS]
{
	int		*colors;
	int		i;

	colors = (int *)malloc(sizeof(int) * 3);
	if (!colors)
		err_msg_and_free(MALLOC_ERR, map_data);
	i = 0;
	while (i < 3)
	{
		if (ft_strlen(color_arr[i]) > 3)
			err_msg_and_free("Rgb color error : should be between 0 and 255\n", map_data);
		colors[i] = ft_atoi(color_arr[i]);
		if (colors[i] > 255 || colors[i] < 0)
			err_msg_and_free("Rgb color error : should be between 0 and 255\n", map_data);
		i++;
	}
	if (!ft_strncmp("C ", line, 2) && map_data->ceil_col == NULL)
		map_data->ceil_col = colors;
	else if (!ft_strncmp("F ", line, 2) && map_data->floor_col == NULL)
		map_data->floor_col = colors;
	else
	{
		free(colors);
		err_msg_and_free("One or several map paramaters have been duplicated", map_data);
	}
}

static void	parse_up_and_down(t_map_data *map_data, char *line) // to test
{
	char	*color_arr;
	char	*info;
	int		i;

	line = line + 3;
	if (!line[0])
		err_msg_and_free(FORMAT_MAP_ERR, map_data);
	info = ft_strtrim(line, " \t\v\f\r");
	if (!info)
		err_msg_and_free(MALLOC_ERR, map_data);
	i = 0;
	while (line && line[i])
	{
		if (line[i] != ',' && ft_isdigit(line[i]) == 0)
		{
			free(info);
			err_msg_and_free("Rgb color error : should be between 0 and 255\n", map_data);
		}
		i++;
	}
	color_arr = ft_split(info, ',');
	free(info);
	if (!color_arr)
		err_msg_and_free(MALLOC_ERR, map_data);
	convert_to_intarr(map_data, line, color_arr);
}

void	parse_infos(t_map_data *map_data) // to test
{
	int		i;
	char	*line;

	i = 0;
	while (map_data->cub && map_data->cub[i] && map_data->nb_infos < 6)
	{
		line = map_data->cub[i];
		while (ft_isspace(line))
			line++;
		if (ft_strlen(line) >= 3 && (!ft_strncmp("NO ", line, 3)
			|| !ft_strncmp("SO ", line, 3) || !ft_strncmp("EA ", line, 3)
			|| !ft_strncmp("WE ", line, 3)))
			parse_card_points(map_data, line);
		else if ( ft_strlen(line) >= 3 &&
			(!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)))
			parse_up_and_down(map_data, line);
		else
			err_msg_and_free(FORMAT_MAP_ERR, map_data);
		map_data->nb_infos++;
		i++;
	}
	if (map_data->nb_infos != 6)
		err_msg_and_free(NB_PARAMS_ERR, map_data);
	parse_map(map_data, i);
}
