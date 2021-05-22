/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:06:57 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/03 15:41:00 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			cal_sprite_order_dist(t_game *game)
{
	int			idx;
	int			x;
	int			y;

	idx = 0;
	while (idx < game->sprite.num)
	{
		game->sprite.s_order[idx] = idx;
		x = game->player.pos.x - game->sprite.pos[idx].x;
		y = game->player.pos.y - game->sprite.pos[idx].y;
		game->sprite.s_dist[idx] = (x * x) + (y * y);
		idx++;
	}
	sort_sprites(game);
}

void			cal_sprite_matrix(t_game *game, t_s_draw *s_d, int order)
{
	s_d->s_pos.x = game->sprite.pos[order].x - game->player.pos.x;
	s_d->s_pos.y = game->sprite.pos[order].y - game->player.pos.y;
	s_d->inv_det = 1.0 / (game->player.plain.x * game->player.dir.y -
							game->player.dir.x * game->player.plain.y);
	s_d->transform.x = s_d->inv_det * (game->player.dir.y * s_d->s_pos.x -
										game->player.dir.x * s_d->s_pos.y);
	s_d->transform.y = s_d->inv_det * (-game->player.plain.y * s_d->s_pos.x +
										game->player.plain.x * s_d->s_pos.y);
	s_d->s_screen_x = (int)((game->width / 2) *
						(1 + s_d->transform.x / s_d->transform.y));
}

void			cal_sprite_set_range(t_game *game, t_s_draw *s_d)
{
	s_d->s_height = abs((int)(game->height / s_d->transform.y));
	s_d->draw_start.y = -(s_d->s_height) / 2 + game->height / 2;
	if (s_d->draw_start.y < 0)
		s_d->draw_start.y = 0;
	s_d->draw_end.y = s_d->s_height / 2 + game->height / 2;
	if (s_d->draw_end.y >= game->height)
		s_d->draw_end.y = game->height - 1;
	s_d->s_width = abs((int)(game->height / s_d->transform.y));
	s_d->draw_start.x = -(s_d->s_width) / 2 + s_d->s_screen_x;
	if (s_d->draw_start.x < 0)
		s_d->draw_start.x = 0;
	s_d->draw_end.x = s_d->s_width / 2 + s_d->s_screen_x;
	if (s_d->draw_end.x >= game->width)
		s_d->draw_end.x = game->width - 1;
}

void			set_sprite_color(t_game *game, t_s_draw *s_d)
{
	t_point		st;
	t_img		*img;

	st.x = s_d->draw_start.x;
	img = game->sprite.img;
	while (st.x < s_d->draw_end.x)
	{
		s_d->tex.x = (int)((256 * (st.x - (-s_d->s_width / 2 + s_d->s_screen_x))
					* img->img_width / s_d->s_width) / 256);
		if (s_d->transform.y > 0 && st.x > 0 && st.x < game->width
			&& s_d->transform.y < game->z_buf[(int)st.x])
			set_sprite_color_y(game, s_d, &st);
		st.x++;
	}
}

void			draw_sprite(t_game *game)
{
	int			idx;
	t_s_draw	s_d;

	if (game->sprite.num == 0)
		return ;
	cal_sprite_order_dist(game);
	idx = 0;
	while (idx < game->sprite.num)
	{
		cal_sprite_matrix(game, &s_d, idx);
		cal_sprite_set_range(game, &s_d);
		set_sprite_color(game, &s_d);
		idx++;
	}
}
