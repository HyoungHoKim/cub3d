/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:24:31 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:31:54 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_print_by_option(va_list ap, t_option *save, int slen)
{
	int			len;

	len = 0;
	if (save->type == 'c')
		len = ft_print_char(ap, save);
	else if (save->type == 's')
		len = ft_print_string(ap, save);
	else if (save->type == 'p')
		len = ft_print_pointer(ap, save);
	else if (save->type == 'x' || save->type == 'X')
		len = ft_print_x(ap, save);
	else if (save->type == 'd' || save->type == 'i')
		len = ft_print_di(ap, save);
	else if (save->type == 'u')
		len = ft_print_u(ap, save);
	else if (save->type == '%')
		len = ft_print_percent(save);
	else if (save->type == 'n')
		ft_print_n(ap, slen);
	else if (save->type == 'f')
		ft_print_f(ap, save);
	else
		return (-1);
	return (len);
}

int				ft_printf_format(const char *format, va_list ap,
								int *len, int idx)
{
	t_option	*save;

	if (!(save = (t_option*)malloc(sizeof(t_option))))
		return (-1);
	if ((idx = ft_initial_option(format, ap, idx, &save)) == -1)
		return (-1);
	(*len) += ft_print_by_option(ap, save, *len);
	if (save)
		free(save);
	return (idx);
}

int				ft_printf(const char *format, ...)
{
	int			idx;
	int			len;
	va_list		ap;

	idx = 0;
	len = 0;
	va_start(ap, format);
	while (format[idx])
	{
		if (format[idx] == '%')
		{
			if ((idx = ft_printf_format(format, ap, &len, idx)) == -1)
				return (-1);
		}
		else
		{
			write(1, &format[idx], 1);
			len++;
		}
		idx++;
	}
	return (len);
}
