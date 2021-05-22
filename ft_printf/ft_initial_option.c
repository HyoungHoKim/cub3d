/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initial_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:14:40 by hhk               #+#    #+#             */
/*   Updated: 2021/01/20 07:13:58 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_flag(const char *format, int pos, t_option *save)
{
	int			idx;

	idx = pos;
	save->is_minus = false;
	save->is_zero = false;
	while (format[idx])
	{
		if (format[idx] == '-')
			save->is_minus = true;
		else if (format[idx] == '0')
			save->is_zero = true;
		else
			break ;
		idx++;
	}
	return (idx);
}

int				check_width(const char *format, va_list ap,
							int pos, t_option *save)
{
	int			idx;

	idx = pos;
	save->width = 0;
	if (format[idx] == '*')
	{
		save->width = va_arg(ap, int);
		idx++;
	}
	else if (ft_isdigit(format[idx]))
	{
		while (ft_isdigit(format[idx]))
			save->width = save->width * 10 + (format[idx++] - '0');
	}
	return (idx);
}

int				check_precision(const char *format, va_list ap,
							int pos, t_option *save)
{
	int			idx;

	idx = pos;
	save->precision = -1;
	if (format[idx] == '.')
	{
		idx++;
		if (format[idx] == '*')
		{
			save->precision = va_arg(ap, int);
			idx++;
		}
		else if (ft_isdigit(format[idx]))
		{
			save->precision = 0;
			while (ft_isdigit(format[idx]))
				save->precision = save->precision * 10 + (format[idx++] - '0');
		}
		else
			save->precision = 0;
	}
	return (idx);
}

int				check_specifier(const char *format, int pos, t_option *save)
{
	if (format[pos] == 'c')
		save->type = 'c';
	else if (format[pos] == 's')
		save->type = 's';
	else if (format[pos] == 'p')
		save->type = 'p';
	else if (format[pos] == 'd')
		save->type = 'd';
	else if (format[pos] == 'i')
		save->type = 'i';
	else if (format[pos] == 'u')
		save->type = 'u';
	else if (format[pos] == 'x')
		save->type = 'x';
	else if (format[pos] == 'X')
		save->type = 'X';
	else if (format[pos] == '%')
		save->type = '%';
	else if (format[pos] == 'n')
		save->type = 'n';
	else if (format[pos] == 'f')
		save->type = 'f';
	else
		return (-1);
	return (pos);
}

int				ft_initial_option(const char *format, va_list ap,
								int pos, t_option **save)
{
	pos = check_flag(format, pos + 1, *save);
	pos = check_width(format, ap, pos, *save);
	pos = check_precision(format, ap, pos, *save);
	return (check_specifier(format, pos, *save));
}
