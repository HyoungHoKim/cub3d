/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:25:12 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 16:32:18 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		draw_player_pos(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = (game->player.pos.x - 0.001) * 10;
	j = (game->player.pos.y - 0.001) * 10;
	x = i + 5;
	y = j + 5;
	while (j < y)
	{
		i = (game->player.pos.x - 0.001) * 10;
		while (i < x)
		{
			game->img.data[(10 + j) *
				(game->img.size_l / 4) + (i + 10)] = 0xFF0000;
			i++;
		}
		j++;
	}
}

void		select_color(t_game *game, int x, int y, int *color)
{
	if (game->map[y][x] == '0' || game->map[y][x] == 'N'
		|| game->map[y][x] == 'E' || game->map[y][x] == 'W'
		|| game->map[y][x] == 'S')
		*color = 0xFFFFFF;
	else if (game->map[y][x] == '2')
		*color = 0x00AA00;
	else if (game->map[y][x] == '1')
		*color = 0x000000;
	else
		*color = -1;
}

void		draw_rectangle(t_game *game, int x, int y, int color)
{
	int		i;
	int		j;

	x *= 10;
	y *= 10;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (color != -1)
				game->img.data[(10 + y + i) *
					(game->img.size_l / 4) + x + j + 10] = color;
			j++;
		}
		i++;
	}
}

void		draw_rectangles(t_game *game)
{
	char	**temp;
	int		i;
	int		j;
	int		len;
	int		color;

	temp = game->map;
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		len = (int)ft_strlen(temp[i]);
		while (j < len)
		{
			select_color(game, j, i, &color);
			draw_rectangle(game, j, i, color);
			j++;
		}
		i++;
	}
}

void		draw_minimap(t_game *game)
{
	if (game->rows * 10 + 10 < game->height / 2 ||
		game->cols * 10 + 10 < game->width / 2)
	{
		draw_rectangles(game);
		draw_player_pos(game);
	}
}
