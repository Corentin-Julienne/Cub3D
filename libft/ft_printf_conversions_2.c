/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:26:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 13:12:50 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_handle_unsigned_int(t_parse *parse_tab)
{
	unsigned int	res;
	char			*res_to_a;
	size_t			numlen;

	res = va_arg(parse_tab->args, int);
	res_to_a = ft_lltoa(res);
	if (!res_to_a)
	{
		parse_tab->rtn = -1;
		return ;
	}
	numlen = ft_strlen(res_to_a);
	parse_tab->rtn = parse_tab->rtn + numlen;
	ft_putlnbr_fd(res, 1);
	free(res_to_a);
}

void	ft_handle_hxd_num(t_parse *parse_tab)
{
	unsigned int	res;

	res = va_arg(parse_tab->args, unsigned int);
	parse_tab->rtn = parse_tab->rtn + ft_intlen_base(res, 16);
	ft_putlnbr_base(res, "0123456789abcdef");
}

void	ft_handle_upper_hxd_num(t_parse *parse_tab)
{
	unsigned int	res;

	res = va_arg(parse_tab->args, unsigned int);
	parse_tab->rtn = parse_tab->rtn + ft_intlen_base(res, 16);
	ft_putlnbr_base(res, "0123456789ABCDEF");
}
