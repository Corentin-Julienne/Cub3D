/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:33:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 10:36:04 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_err_msg(const char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
