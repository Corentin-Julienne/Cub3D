/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/02 02:32:40 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* when an error is encountered, print Error\n, followed by a relevant
error msg. then, free the map struct to avoid leaks and exit status 1 */

void	err_msg_and_free(char *spec, t_infomap *infomap)
{
	char		*msg;

	msg = "Error\n";
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(spec, STDERR_FILENO);
	free_map(infomap);
	exit(EXIT_FAILURE);
}

/* same as err_msg_and_free but with the game structure to free */

void	err_msg_and_free_all(char *spec, t_game *game)
{
	t_infomap	*infomap;

	infomap = game->infomap;
	
	// TODO: Free game structure here

	err_msg_and_free(spec, infomap);
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
