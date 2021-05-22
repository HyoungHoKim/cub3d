/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type_bonus1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:31:31 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:17:18 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_print_n(va_list ap, int len)
{
	int			*num;

	num = va_arg(ap, int*);
	(*num) = len;
}

void			f_print_precision2(char *str, double fraction, t_option *save)
{
	int			idx;
	int			pos;
	char		*temp;

	idx = 0;
	while ((fraction < 0.1) && (idx < save->precision))
	{
		str[idx++] = '0';
		fraction *= 10;
	}
	pos = idx;
	while (idx++ < save->precision)
		fraction *= 10;
	temp = ft_maxitoa(ft_round(fraction));
	ft_memcpy(str + pos, temp, save->precision - pos);
	temp[save->precision] = '\0';
	free(temp);
}

char			*f_print_precision(char *str, double fraction, t_option *save)
{
	char		*temp;
	char		*temp2;

	temp = (char*)malloc(sizeof(char) * (save->precision + 1));
	if (fraction == 0.0)
		ft_memset(temp, '0', save->precision);
	else if (save->precision)
		f_print_precision2(temp, fraction, save);
	temp2 = str;
	str = ft_strjoin(str, temp);
	free(temp);
	free(temp2);
	return (str);
}

char			*print_fraction(char *str, double fraction, t_option *save)
{
	if (save->precision == -1)
		save->precision = 6;
	str = f_print_precision(str, fraction, save);
	return (str);
}

int				ft_print_f(va_list ap, t_option *save)
{
	double		num;
	uint64_t	dec;
	double		fraction;
	char		*ans;
	bool		is_minus;

	is_minus = false;
	num = va_arg(ap, double);
	if (is_denormalized(num, &is_minus))
		return (-1);
	if (num < 0)
		num *= -1;
	dec = (uint64_t)num;
	fraction = num - dec;
	ans = ft_print_f_decimal(num, dec, save, is_minus);
	ans = print_fraction(ans, fraction, save);
	ans = ft_print_di_width(ans, save);
	write(1, ans, ft_strlen(ans));
	return (ft_strlen(ans));
}
