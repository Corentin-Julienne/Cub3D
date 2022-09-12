/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:43:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 13:12:56 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_parse	*ft_initialize_data(t_parse *parse_tab, const char *format)
{
	parse_tab->rtn = 0;
	parse_tab->format = format;
	parse_tab->i = 0;
	return (parse_tab);
}

void	ft_find_format(t_parse *parse_tab, int index)
{
	if (parse_tab->format[index] == 'c')
		ft_handle_char(parse_tab);
	else if (parse_tab->format[index] == '%')
		ft_handle_percent(parse_tab);
	else if (parse_tab->format[index] == 's')
		ft_handle_string(parse_tab);
	else if (parse_tab->format[index] == 'p')
		ft_handle_void_pointer(parse_tab);
	else if (parse_tab->format[index] == 'd')
		ft_handle_signed_int(parse_tab);
	else if (parse_tab->format[index] == 'i')
		ft_handle_signed_int(parse_tab);
	else if (parse_tab->format[index] == 'u')
		ft_handle_unsigned_int(parse_tab);
	else if (parse_tab->format[index] == 'x')
		ft_handle_hxd_num(parse_tab);
	else if (parse_tab->format[index] == 'X')
		ft_handle_upper_hxd_num(parse_tab);
}

t_parse	*ft_create_parse_tab(const char *format)
{
	t_parse		*parse_tab;

	parse_tab = (t_parse *)malloc(sizeof(t_parse));
	if (!parse_tab)
		return (NULL);
	parse_tab = ft_initialize_data(parse_tab, format);
	return (parse_tab);
}

void	ft_printer(t_parse *parse_tab)
{
	while (parse_tab->format[parse_tab->i])
	{
		if (parse_tab->format[parse_tab->i] == '%')
		{
			ft_find_format(parse_tab, parse_tab->i + 1);
			if (parse_tab->rtn == -1)
				return ;
			parse_tab->i++;
		}		
		else
		{
			ft_putchar_fd(parse_tab->format[parse_tab->i], 1);
			parse_tab->rtn++;
		}	
		parse_tab->i++;
	}
}

int	ft_printf(const char *format, ...)
{
	t_parse		*parse_tab;
	int			rtn_val;

	parse_tab = ft_create_parse_tab(format);
	if (!parse_tab)
		return (-1);
	va_start(parse_tab->args, format);
	ft_printer(parse_tab);
	if (parse_tab->rtn == -1)
	{
		rtn_val = -1;
		free(parse_tab);
		return (rtn_val);
	}
	va_end(parse_tab->args);
	rtn_val = parse_tab->rtn;
	free(parse_tab);
	return (rtn_val);
}
