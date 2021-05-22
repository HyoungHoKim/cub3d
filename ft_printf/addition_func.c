/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:27:46 by hhk               #+#    #+#             */
/*   Updated: 2021/01/23 14:50:19 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*utoa(unsigned long long address)
{
	char				*hexa_base;
	unsigned long long	temp;
	char				*ans;
	int					len;

	hexa_base = "0123456789abcdef";
	temp = address;
	len = 1;
	while (temp >= 16)
	{
		temp /= 16;
		len++;
	}
	ans = (char*)malloc(sizeof(char) * len + 1);
	ans[len] = '\0';
	while (address >= 16)
	{
		ans[--len] = hexa_base[(address % 16)];
		address /= 16;
	}
	ans[0] = hexa_base[address];
	return (ans);
}

char					*inputnum(long long n, int len)
{
	char				*answer;

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

char					*ft_uitoa(unsigned int n)
{
	char				*answer;
	unsigned int		num;
	int					size;

	num = n;
	size = 1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	answer = inputnum(num, size);
	return (answer);
}
