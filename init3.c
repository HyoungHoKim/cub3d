/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:37:40 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/13 18:36:03 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			save_player_origin(t_game *game, char c, int x, int y)
{
	if (game->player.pos.x == -1 && game->player.pos.y == -1)
	{
		set_point(&game->player.pos, x + 0.001, y + 0.001);
		set_dir_plain(game, c);
	}
	else
		return (0);
	return (1);
}

void		get_sprite_num(t_game *game)
{
	int		x;
	int		y;
	char	num;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			num = game->map[y][x];
			if (num == '2')
				game->sprite.num++;
			x++;
		}
		y++;
	}
}

char		**init_test_map(t_game *game)
{
	int		y;
	char	**test_map;

	y = 0;
	test_map = (char**)malloc(sizeof(char*) * (game->rows + 2));
	if (!test_map)
		return (NULL);
	while (y < game->rows + 2)
	{
		test_map[y] = (char*)malloc(sizeof(char) * (game->cols + 3));
		if (!test_map[y])
			return (NULL);
		ft_memset(test_map[y], ' ', game->cols + 2);
		test_map[y][game->cols + 2] = '\0';
		y++;
	}
	return (test_map);
}

void		init_player_data(t_game *game)
{
	game->player.pos.x = -1;
	game->player.pos.y = -1;
	game->player.plain.x = 0;
	game->player.plain.y = 0.66;
	game->player.move_speed = 0.1;
	game->player.rot_speed = 0.1;
}
