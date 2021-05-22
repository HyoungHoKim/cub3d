/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:26:01 by hhk               #+#    #+#             */
/*   Updated: 2021/01/15 19:26:07 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_print_char_width(char c, t_option *save, bool isleft)
{
	char	*ans;

	if (save->width <= 1)
	{
		write(1, &c, 1);
		return (1);
	}
	else
	{
		ans = (char*)malloc(sizeof(char) * save->width + 1);
		ans[save->width] = '\0';
		ft_memset(ans, ' ', save->width);
		if (isleft || save->is_minus)
			ans[0] = c;
		else
			ans[save->width - 1] = c;
		write(1, ans, save->width);
		free(ans);
		return (save->width);
	}
}

int			ft_print_char(va_list ap, t_option *save)
{
	char	c;
	bool	isleft;

	c = va_arg(ap, int);
	isleft = false;
	if (save->width < 0)
	{
		save->width *= -1;
		isleft = true;
	}
	return (ft_print_char_width(c, save, isleft));
}

int			ft_print_string_width_over(char *str, t_option *save, bool isleft)
{
	char	*ans;
	int		len;

	len = ft_strlen(str);
	ans = (char*)malloc(sizeof(char) * save->width + 1);
	ans[save->width] = '\0';
	ft_memset(ans, ' ', save->width);
	if (isleft || save->is_minus)
		ft_memcpy(ans, str, len);
	else
	{
		if (save->is_zero && save->precision < 0)
			ft_memset(ans, '0', save->width);
		ft_memcpy(ans + (save->width - len), str, len);
	}
	write(1, ans, save->width);
	free(ans);
	return (save->width);
}

int			ft_print_string_width(char *str, t_option *save)
{
	int		len;
	bool	isleft;

	len = ft_strlen(str);
	isleft = false;
	if (save->width < 0)
	{
		save->width *= -1;
		isleft = true;
	}
	if (save->width <= len)
	{
		write(1, str, len);
		return (len);
	}
	else
		return (ft_print_string_width_over(str, save, isleft));
}

int			ft_print_string(va_list ap, t_option *save)
{
	char	*str;
	int		len;

	str = va_arg(ap, char*);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (save->precision == 0)
		return (ft_print_string_width("", save));
	if ((save->precision < len) && (save->precision > 0))
		str = ft_substr(str, 0, save->precision);
	len = ft_print_string_width(str, save);
	if ((save->precision < (int)ft_strlen(str)) && (save->precision > 0))
		free(str);
	return (len);
}
