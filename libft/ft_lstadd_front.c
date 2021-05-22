/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:24:54 by hhk               #+#    #+#             */
/*   Updated: 2021/02/05 12:21:49 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	else
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
