/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_func_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:34:38 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:34:02 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool				is_denormalized(double num, bool *is_minus)
{
	uint64_t		num_bit;
	double			d_num;

	d_num = num;
	num_bit = *(uint64_t*)&d_num;
	if (num_bit >> 63)
		*is_minus = true;
	if (((num_bit >> 52) & 0xFFF) == 0xFFF)
	{
		if (num_bit & 0x000FFFFFFFFFFFFF)
			write(1, "-nan", 4);
		else
			write(1, "-inf", 4);
		return (true);
	}
	else if (((num_bit >> 52) & 0xFFF) == 0x7FF)
	{
		if (num_bit & 0x000FFFFFFFFFFFFF)
			write(1, "nan", 3);
		else
			write(1, "inf", 3);
		return (true);
	}
	return (false);
}

char				*input_maxnum(intmax_t n, int len)
{
	char			*answer;

	if (!(answer = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	answer[len] = '\0';
	len = len - 1;
	while (len >= 0 && n >= 10)
	{
		answer[len] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	answer[0] = '0' + n;
	return (answer);
}

char				*ft_maxitoa(intmax_t n)
{
	char			*answer;
	intmax_t		num;
	int				size;

	num = n;
	size = 1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	answer = input_maxnum(num, size);
	return (answer);
}

intmax_t			ft_round(double f)
{
	intmax_t		integer;
	double			decimal;

	integer = (intmax_t)f;
	decimal = f - integer;
	if (f >= 0)
		return ((decimal < 0.5) ? integer : integer + 1);
	else
		return ((decimal > 0.5) ? integer : integer - 1);
}
