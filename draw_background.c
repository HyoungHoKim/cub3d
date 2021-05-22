/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:04:57 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/11 13:42:44 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			set_default_bg(t_game *game, int x)
{
	int		y;

	y = 0;
	if (game->background[0] == -1 || game->background[1] == -1)
		return (0);
	while (y < game->height)
	{
		game->buf[y][x] = game->background[1];
		game->buf[game->height - y - 1][x] = game->background[0];
		y++;
	}
	return (1);
}
