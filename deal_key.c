/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 08:39:15 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 22:50:24 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		move_front(t_game *game)
{
	t_point	pos;
	t_point	dir;
	double	move_speed;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	dir.x = game->player.dir.x;
	dir.y = game->player.dir.y;
	move_speed = game->player.move_speed;
	if ('1' != game->map[(int)(pos.y + dir.y * move_speed)][(int)(pos.x)] &&
	'2' != game->map[(int)(pos.y + dir.y * move_speed)][(int)(pos.x)])
		game->player.pos.y += dir.y * move_speed;
	if ('1' != game->map[(int)(pos.y)][(int)(pos.x + dir.x * move_speed)] &&
	'2' != game->map[(int)(pos.y)][(int)(pos.x + dir.x * move_speed)])
		game->player.pos.x += dir.x * move_speed;
}

void		move_back(t_game *game)
{
	t_point	pos;
	t_point	dir;
	double	move_speed;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	dir.x = game->player.dir.x;
	dir.y = game->player.dir.y;
	move_speed = game->player.move_speed;
	if ('1' != game->map[(int)(pos.y - dir.y * move_speed)][(int)(pos.x)] &&
	'2' != game->map[(int)(pos.y - dir.y * move_speed)][(int)(pos.x)])
		game->player.pos.y -= dir.y * move_speed;
	if ('1' != game->map[(int)(pos.y)][(int)(pos.x - dir.x * move_speed)] &&
	'2' != game->map[(int)(pos.y)][(int)(pos.x - dir.x * move_speed)])
		game->player.pos.x -= dir.x * move_speed;
}

void		rot_right(t_game *game)
{
	double	old_d_x;
	double	old_p_x;
	double	rot_speed;
	t_point dir;
	t_point plain;

	old_d_x = game->player.dir.x;
	old_p_x = game->player.plain.x;
	rot_speed = game->player.rot_speed;
	dir.x = game->player.dir.x;
	dir.y = game->player.dir.y;
	plain.x = game->player.plain.x;
	plain.y = game->player.plain.y;
	game->player.dir.x = dir.x * cos(rot_speed) - dir.y * sin(rot_speed);
	game->player.dir.y = old_d_x * sin(rot_speed) + dir.y * cos(rot_speed);
	game->player.plain.x = plain.x * cos(rot_speed) - plain.y * sin(rot_speed);
	game->player.plain.y = old_p_x * sin(rot_speed) + plain.y * cos(rot_speed);
}

void		rot_left(t_game *game)
{
	double	old_d_x;
	double	old_p_x;
	double	rot_speed;
	t_point dir;
	t_point p;

	old_d_x = game->player.dir.x;
	old_p_x = game->player.plain.x;
	rot_speed = game->player.rot_speed;
	dir.x = game->player.dir.x;
	dir.y = game->player.dir.y;
	p.x = game->player.plain.x;
	p.y = game->player.plain.y;
	game->player.dir.x = dir.x * cos(-rot_speed) - dir.y * sin(-rot_speed);
	game->player.dir.y = old_d_x * sin(-rot_speed) + dir.y * cos(-rot_speed);
	game->player.plain.x = p.x * cos(-rot_speed) - p.y * sin(-rot_speed);
	game->player.plain.y = old_p_x * sin(-rot_speed) + p.y * cos(-rot_speed);
}

int			deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
	{
		free_t_game(game);
		exit(0);
	}
	if (key_code == KEY_W)
		move_front(game);
	if (key_code == KEY_S)
		move_back(game);
	if (key_code == KEY_D)
		move_right(game);
	if (key_code == KEY_A)
		move_left(game);
	if (key_code == KEY_RIGHT)
		rot_right(game);
	if (key_code == KEY_LEFT)
		rot_left(game);
	if (key_code == KEY_M)
	{
		if (game->game_mode == 2)
			game->game_mode = 0;
		else if (game->game_mode == 0)
			game->game_mode = 2;
	}
	return (0);
}
