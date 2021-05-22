/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:52:30 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 15:03:09 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_game		*game_init(bool is_save)
{
	t_game	*game;
	int		idx;

	game = (t_game*)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->width = -1;
	game->height = -1;
	game->cols = -1;
	game->rows = -1;
	game->x_tiles = -1;
	game->y_tiles = -1;
	game->map = NULL;
	game->game_mode = is_save;
	game->background[0] = -1;
	game->background[1] = -1;
	idx = 0;
	while (idx < 4)
		game->tex_path[idx++] = NULL;
	init_player_data(game);
	game->sprite.num = 0;
	return (game);
}

int			window_init(t_game *game)
{
	if (game->width <= 0 || game->height <= 0)
		return (0);
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
	return (1);
}

void		img_init(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, game->width, game->height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
									&game->img.size_l, &game->img.endian);
}

void		reinit_img(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			game->img.data[y * (game->img.size_l / 4) + x] = 0x000000;
			x++;
		}
		y++;
	}
}

int			init_player(t_game *game)
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
			if (num == 'N' || num == 'S' || num == 'E' || num == 'W')
				if (!save_player_origin(game, num, x, y))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}
