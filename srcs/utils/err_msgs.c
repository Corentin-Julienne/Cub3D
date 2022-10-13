/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/13 13:16:11 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

/* when an error is encountered, print Error\n, followed by a relevant
error msg. then, free the map struct to avoid leaks and exit status 1 */

void	err_msg_and_free_map(char *spec, t_infomap *infomap)
{
	free_map(&infomap);
	print_err_msg(spec);
}

/* same as err_msg_and_free_map but with the game structure to free */

void	err_msg_and_free_all(char *spec, t_game *game)
{
	free_game(&game);
	print_err_msg(spec);
}
