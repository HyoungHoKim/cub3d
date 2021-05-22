/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:15:39 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 15:02:07 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		free_buf_map(t_game *game)
{
	int		h;

	h = 0;
	if (game->buf)
	{
		while (h < game->height)
			free(game->buf[h++]);
		free(game->buf);
	}
	h = 0;
	if (game->map)
	{
		while (h < game->rows)
			free(game->map[h++]);
		free(game->map);
	}
}

void		free_sprite(t_game *game)
{
	if (game->sprite.img)
		free(game->sprite.img);
	if (game->sprite.path)
		free(game->sprite.path);
	if (game->sprite.pos)
		free(game->sprite.pos);
	if (game->sprite.s_dist)
		free(game->sprite.s_dist);
	if (game->sprite.s_order)
		free(game->sprite.s_order);
}

void		free_t_game(t_game *game)
{
	int		idx;

	if (!game)
		return ;
	if (game->mlx || game->win)
	{
		if (game->mlx && game->win)
			mlx_destroy_window(game->mlx, game->win);
		else if (game->mlx && !game->win)
			free(game->mlx);
	}
	idx = 0;
	while (idx < 4)
	{
		if (game->tex_path[idx])
			free(game->tex_path[idx]);
		idx++;
	}
	free_buf_map(game);
	if (game->z_buf)
		free(game->z_buf);
	free_sprite(game);
	if (game)
		free(game);
}

void		max_window_size(t_game *game)
{
	int max_x;
	int max_y;

	mlx_get_screen_size(game->mlx, &max_x, &max_y);
	if (game->width > max_x)
		game->width = max_x;
	if (game->height > max_y)
		game->height = max_y;
}
