/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:09:20 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 06:56:17 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Since I had a few problems with results being X.999999 because of PI,
I made this function in order to ceil the double in case this is all 999999.
Even if this is make by error (really low probability),
it will not change anything. */

double	ceil_double(double nb)
{
	double		tmp;

	tmp = nb;
	if (nb - (int)nb > 0.99999)
		tmp = (int)nb + 1;
	if (nb - (int)nb < 0.00001)
		tmp = (int)nb;
	return (tmp);
}

/* Calculate the distance between 2 points */

double	calc_dist(double x1, double y1, double x2, double y2)
{
	double	dist;

	dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return (dist);
}
