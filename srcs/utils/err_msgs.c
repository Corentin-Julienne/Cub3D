/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 16:58:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* when an error is encountered, print Error\n, followed by a relevant
error msg. then, free the map_data struct to avoid leaks and exit status 1 */

void	err_msg_and_free(char *spec, t_map_data *map_data)
{
	char		*msg;

	msg = "Error\n";
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(spec, STDERR_FILENO);
	free_map_data(map_data);
	exit(EXIT_FAILURE);
}

/* print Error\n when error encountered, then print a relevant msg,
then exit with exit status 1 */

void	print_err_msg(char *spec)
{
	char		*msg;

	msg = "Error\n";
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(spec, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
