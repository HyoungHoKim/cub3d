/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:26:01 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:30:26 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_print_di_width_over(char *str, t_option *save, bool isleft)
{
	char	*ans;
	int		len;

	len = ft_strlen(str);
	ans = (char*)malloc(sizeof(char) * (save->width + 1));
	ft_memset(ans, ' ', save->width);
	if (isleft || save->is_minus)
		ft_memcpy(ans, str, len);
	else
	{
		if (save->is_zero && save->precision < 0)
			ft_memset(ans, '0', save->width);
		if (ft_strchr(str, '-') && (save->is_zero && save->precision < 0))
		{
			ans[0] = '-';
			ft_memcpy(ans + 1 + (save->width - len), str + 1, len);
		}
		else
			ft_memcpy(ans + (save->width - len), str, len);
	}
	ans[save->width] = '\0';
	free(str);
	return (ans);
}

char		*ft_print_di_width(char *str, t_option *save)
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
		return (str);
	else
		return (ft_print_di_width_over(str, save, isleft));
}

char		*di_precision_minus(char *str, t_option *save, bool is_minus)
{
	int		len;
	int		new_len;
	char	*ans;

	len = ft_strlen(str);
	new_len = save->precision + 1;
	if (is_minus)
		new_len = save->precision + 2;
	ans = (char*)malloc(sizeof(char) * (new_len));
	ft_memset(ans, '0', new_len - 1);
	if (is_minus)
	{
		ans[0] = '-';
		ft_memcpy(ans + 1 + (save->precision - len + 1), str + 1, len);
	}
	else
		ft_memcpy(ans + (save->precision - len), str, len);
	ans[new_len - 1] = '\0';
	free(str);
	return (ans);
}

char		*ft_print_di_precision(char *str, t_option *save, bool is_minus)
{
	int		len;

	len = ft_strlen(str);
	if (save->precision >= len)
		return (di_precision_minus(str, save, is_minus));
	return (str);
}

int			ft_print_di(va_list ap, t_option *save)
{
	int		num;
	char	*ans;
	bool	is_minus;
	int		len;

	is_minus = false;
	num = va_arg(ap, int);
	if (num < 0)
		is_minus = true;
	if (save->precision == 0 && num == 0)
		ans = ft_strdup("");
	else
		ans = ft_itoa(num);
	ans = ft_print_di_precision(ans, save, is_minus);
	ans = ft_print_di_width(ans, save);
	len = ft_strlen(ans);
	write(1, ans, len);
	free(ans);
	return (len);
}
