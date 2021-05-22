/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:28:46 by marvin            #+#    #+#             */
/*   Updated: 2020/12/23 15:28:25 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha(int c)
{
	int check;

	check = 1;
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
		check = 0;
	return (check);
}