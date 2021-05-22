/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_by_type_bonus2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:49:02 by hyoukim           #+#    #+#             */
/*   Updated: 2021/01/23 14:37:42 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_print_f_decimal(double num, uint64_t dec,
								t_option *save, bool is_minus)
{
	char	*ans;
	char	*temp;

	if (save->precision == 0)
		ans = ft_maxitoa(ft_round(num));
	else
		ans = ft_maxitoa(dec);
	if (is_minus)
	{
		temp = ft_strjoin("-", ans);
		free(ans);
		ans = temp;
	}
	temp = ft_strjoin(ans, ".");
	free(ans);
	ans = temp;
	return (ans);
}
