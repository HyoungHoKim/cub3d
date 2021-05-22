/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:26:01 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:31:32 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_print_pointer(va_list ap, t_option *save)
{
	unsigned long long	address;
	char				*ans;
	char				*temp;
	int					len;

	address = (unsigned long long)va_arg(ap, void*);
	if (save->precision == 0 && address == 0)
		temp = ft_strdup("");
	else
		temp = utoa(address);
	ans = ft_print_x_precision(temp, save);
	ans = ft_strjoin("0x", ans);
	len = ft_print_string_width(ans, save);
	if (ans)
		free(ans);
	return (len);
}

char					*ft_print_x_precision(char *str, t_option *save)
{
	int					len;
	char				*ans;

	len = ft_strlen(str);
	if (save->precision > len)
	{
		ans = (char*)malloc(sizeof(char) * (save->precision + 1));
		ans[save->precision] = '\0';
		ft_memset(ans, '0', save->precision);
		ft_memcpy(ans + (save->precision - len), str, len);
		free(str);
		return (ans);
	}
	return (str);
}

char					*ft_print_x_width_over(char *str, t_option *save,
												bool isleft)
{
	char				*ans;
	int					len;

	len = ft_strlen(str);
	ans = (char*)malloc(sizeof(char) * (save->width + 1));
	ft_memset(ans, ' ', save->width);
	ans[save->width] = '\0';
	if (isleft || save->is_minus)
		ft_memcpy(ans, str, len);
	else
	{
		if (save->is_zero && save->precision < 0)
			ft_memset(ans, '0', save->width);
		ft_memcpy(ans + (save->width - len), str, len);
	}
	free(str);
	return (ans);
}

char					*ft_print_x_width(char *str, t_option *save)
{
	int					len;
	bool				isleft;

	isleft = false;
	if (save->width < 0)
	{
		save->width *= -1;
		isleft = true;
	}
	len = ft_strlen(str);
	if (save->width <= len)
		return (str);
	else
		return (ft_print_x_width_over(str, save, isleft));
}

int						ft_print_x(va_list ap, t_option *save)
{
	unsigned int		num;
	char				*ans;
	int					idx;
	int					len;

	num = va_arg(ap, unsigned int);
	idx = -1;
	if (save->precision == 0 && num == 0)
		ans = ft_strdup("");
	else
		ans = utoa(num);
	ans = ft_print_x_precision(ans, save);
	ans = ft_print_x_width(ans, save);
	if (save->type == 'X')
		while (ans[++idx] != '\0')
			ans[idx] = ft_toupper(ans[idx]);
	len = ft_strlen(ans);
	write(1, ans, len);
	free(ans);
	return (len);
}
