/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:26:01 by hhk               #+#    #+#             */
/*   Updated: 2021/01/15 18:56:41 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_print_u(va_list ap, t_option *save)
{
	unsigned int		num;
	char				*ans;
	int					len;

	num = va_arg(ap, unsigned int);
	if (save->precision == 0 && num == 0)
		ans = ft_strdup("");
	else
		ans = ft_uitoa(num);
	ans = ft_print_x_precision(ans, save);
	ans = ft_print_x_width(ans, save);
	len = ft_strlen(ans);
	write(1, ans, len);
	free(ans);
	return (len);
}

int						ft_print_percent(t_option *save)
{
	char				*c;
	int					len;

	c = (char*)malloc(sizeof(char) * 2);
	c[0] = '%';
	c[1] = '\0';
	c = ft_print_x_width(c, save);
	len = ft_strlen(c);
	write(1, c, len);
	free(c);
	return (len);
}
