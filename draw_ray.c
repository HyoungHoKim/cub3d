/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:17:02 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/02 23:07:28 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		draw_hit(t_game *game, int map_x, int map_y)
{
	int		hit_x;
	int		hit_y;
	int		x;
	int		y;

	hit_x = map_x * game->x_tiles;
	hit_y = map_y * game->y_tiles;
	x = hit_x + 10;
	y = hit_y + 10;
	while (hit_y < y)
	{
		hit_x = map_x * game->x_tiles;
		while (hit_x < x)
		{
			game->img.data[hit_y * (game->img.size_l / 4) + hit_x] = 0xFF0000;
			hit_x++;
		}
		hit_y++;
	}
}

void		init_dda2(t_game *game, t_dda *dda)
{
	if (dda->r_dir.x < 0)
	{
		dda->step.x = -1;
		dda->s_dist.x = (game->player.pos.x - dda->map.x) * dda->d_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->s_dist.x = (dda->map.x + 1.0 - game->player.pos.x) * dda->d_dist.x;
	}
	if (dda->r_dir.y < 0)
	{
		dda->step.y = -1;
		dda->s_dist.y = (game->player.pos.y - dda->map.y) * dda->d_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->s_dist.y = (dda->map.y + 1.0 - game->player.pos.y) * dda->d_dist.y;
	}
}

void		init_dda(t_game *game, t_dda *dda, double camera_x)
{
	dda->r_dir.x = game->player.dir.x + game->player.plain.x * camera_x;
	dda->r_dir.y = game->player.dir.y + game->player.plain.y * camera_x;
	dda->map.x = (int)(game->player.pos.x);
	dda->map.y = (int)(game->player.pos.y);
	dda->d_dist.x = sqrt(1 + (dda->r_dir.y * dda->r_dir.y) /
						(dda->r_dir.x * dda->r_dir.x));
	dda->d_dist.y = sqrt(1 + (dda->r_dir.x * dda->r_dir.x) /
						(dda->r_dir.y * dda->r_dir.y));
	init_dda2(game, dda);
}

int			ray_dda(t_game *game, t_dda *dda)
{
	int		hit;
	char	check;

	hit = 0;
	while (hit == 0)
	{
		if (dda->s_dist.x < dda->s_dist.y)
		{
			dda->s_dist.x += dda->d_dist.x;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->s_dist.y += dda->d_dist.y;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
		check = game->map[(int)dda->map.y][(int)dda->map.x];
		if (check == '1')
			hit = 1;
	}
	return (hit);
}

void		draw_ray(t_game *game)
{
	int		x;
	double	camera_x;
	t_dda	dda;
	int		hit;

	x = 0;
	while (x < game->width)
	{
		camera_x = 2 * x / (double)(game->width) - 1;
		init_dda(game, &dda, camera_x);
		hit = ray_dda(game, &dda);
		if (hit == 1)
			draw_hit(game, dda.map.x, dda.map.y);
		x++;
	}
}
