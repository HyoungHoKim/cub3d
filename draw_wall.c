/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:43:47 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/06 21:45:36 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		image_draw(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			game->img.data[game->img.size_l / 4 * y + x] =
						game->buf[y][(game->width - 1) - x];
			x++;
		}
		y++;
	}
}

int			set_tex_num(t_dda dda)
{
	if (dda.side == 0)
	{
		if (dda.r_dir.x > 0)
			return (3);
		else
			return (2);
	}
	if (dda.side == 1)
	{
		if (dda.r_dir.y > 0)
			return (1);
		else
			return (0);
	}
	return (-1);
}

void		set_wall_tex(t_game *game, t_dda dda, t_point *wall, t_point *tex)
{
	int		tex_num;

	if ((tex_num = set_tex_num(dda)) == -1)
		return ;
	if (dda.side == 0)
		wall->x = game->player.pos.y + dda.perpwalldist * dda.r_dir.y;
	else
		wall->x = game->player.pos.x + dda.perpwalldist * dda.r_dir.x;
	tex->x = (int)((wall->x - floor(wall->x)) *
				(double)game->tex[tex_num].img_width);
	if (dda.side == 0 && dda.r_dir.x < 0)
		tex->x = game->tex[tex_num].img_width - tex->x - 1;
	if (dda.side == 1 && dda.r_dir.y > 0)
		tex->x = game->tex[tex_num].img_width - tex->x - 1;
	wall->y = (dda.draw_start - game->height / 2 + dda.line_h / 2);
}

void		set_textures(t_game *game, t_dda dda, int x)
{
	int		tex_num;
	t_point	wall;
	t_point	tex;
	int		y;
	int		color;

	if ((tex_num = set_tex_num(dda)) == -1)
		return ;
	set_wall_tex(game, dda, &wall, &tex);
	y = dda.draw_start;
	while (y < dda.draw_end)
	{
		tex.y = (int)(game->tex[tex_num].img_height * wall.y / dda.line_h);
		color = game->tex[tex_num].data[(int)(game->tex[tex_num].size_l / 4
										* tex.y + tex.x)];
		if (dda.side == 1)
			color = (color >> 1) & 8355711;
		game->buf[y][x] = color;
		wall.y++;
		y++;
	}
}
