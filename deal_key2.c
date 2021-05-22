/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:04:32 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 22:51:35 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		move_left(t_game *game)
{
	t_point	pos;
	t_point	plain;
	double	move_speed;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	plain.x = game->player.plain.x;
	plain.y = game->player.plain.y;
	move_speed = game->player.move_speed;
	if ('1' != game->map[(int)(pos.y + plain.y * move_speed)][(int)(pos.x)] &&
	'2' != game->map[(int)(pos.y + plain.y * move_speed)][(int)(pos.x)])
		game->player.pos.y += plain.y * move_speed;
	if ('1' != game->map[(int)(pos.y)][(int)(pos.x + plain.x * move_speed)] &&
	'2' != game->map[(int)(pos.y)][(int)(pos.x + plain.x * move_speed)])
		game->player.pos.x += plain.x * move_speed;
}

void		move_right(t_game *game)
{
	t_point	pos;
	t_point	plain;
	double	move_speed;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	plain.x = game->player.plain.x;
	plain.y = game->player.plain.y;
	move_speed = game->player.move_speed;
	if ('1' != game->map[(int)(pos.y - plain.y * move_speed)][(int)(pos.x)] &&
	'2' != game->map[(int)(pos.y - plain.y * move_speed)][(int)(pos.x)])
		game->player.pos.y -= plain.y * move_speed;
	if ('1' != game->map[(int)(pos.y)][(int)(pos.x - plain.x * move_speed)] &&
	'2' != game->map[(int)(pos.y)][(int)(pos.x - plain.x * move_speed)])
		game->player.pos.x -= plain.x * move_speed;
}

int			map_close(t_game *game)
{
	free_t_game(game);
	exit(0);
}
