/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 00:07:56 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 23:00:39 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		cal_dist_height(t_game *game, t_dda *dda)
{
	if (dda->side == 0)
		dda->perpwalldist = (dda->map.x - game->player.pos.x
						+ (1 - dda->step.x) / 2) / dda->r_dir.x;
	else
		dda->perpwalldist = (dda->map.y - game->player.pos.y
						+ (1 - dda->step.y) / 2) / dda->r_dir.y;
	dda->line_h = (int)(game->height / dda->perpwalldist);
	dda->draw_start = (-(dda->line_h) / 2) + game->height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = (dda->line_h / 2) + (game->height / 2);
	if (dda->draw_end >= game->height)
		dda->draw_end = game->height - 1;
}

int			ray_caster(t_game *game)
{
	int		x;
	double	camera_x;
	t_dda	dda;

	x = 0;
	if (game->game_mode == 2)
		floor_casting(game);
	while (x < game->width)
	{
		camera_x = (2 * x / (double)(game->width)) - 1;
		init_dda(game, &dda, camera_x);
		ray_dda(game, &dda);
		if (game->game_mode == 0 || game->game_mode == 1)
		{
			if (!set_default_bg(game, x))
				return (0);
		}
		cal_dist_height(game, &dda);
		game->z_buf[x] = dda.perpwalldist;
		set_textures(game, dda, x);
		x++;
	}
	draw_sprite(game);
	image_draw(game);
	return (1);
}
