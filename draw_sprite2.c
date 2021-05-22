/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:35:22 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/03 15:42:25 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			sort_sprites(t_game *game)
{
	int			i;
	int			j;
	double		temp_d;
	int			temp_o;

	i = 0;
	while (i < game->sprite.num)
	{
		j = 0;
		while (j < game->sprite.num - 1)
		{
			if (game->sprite.s_dist[j] > game->sprite.s_dist[j + 1])
			{
				temp_d = game->sprite.s_dist[j];
				temp_o = game->sprite.s_order[j];
				game->sprite.s_dist[j] = game->sprite.s_dist[j + 1];
				game->sprite.s_order[j] = game->sprite.s_order[j + 1];
				game->sprite.s_dist[j + 1] = temp_d;
				game->sprite.s_order[j + 1] = temp_o;
			}
			j++;
		}
		i++;
	}
}

void			set_sprite_color_y(t_game *game, t_s_draw *s_d, t_point *st)
{
	t_img		*img;
	int			d;
	int			color;

	img = game->sprite.img;
	st->y = s_d->draw_start.y;
	while (st->y < s_d->draw_end.y)
	{
		d = st->y * 256 - game->height * 128 + s_d->s_height * 128;
		s_d->tex.y = ((d * img->img_height) / s_d->s_height) / 256;
		color = img->data[(int)(img->size_l / 4
									* s_d->tex.y + s_d->tex.x)];
		if ((color & 0x00FFFFFF) != 0)
			game->buf[(int)(st->y)][(int)(st->x)] = color;
		st->y++;
	}
}
