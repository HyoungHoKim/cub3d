/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_ceiling_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:56:55 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 22:46:08 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			get_tex_ceiling(t_game *game, t_ceil *ceil)
{
	t_img	*img;

	img = &ceil->img[0];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
										&img->img_width, &img->img_height);
	if (!(img->img_ptr))
		return (0);
	img->data = (int*)mlx_get_data_addr(img->img_ptr, &img->bpp,
										&img->size_l, &img->endian);
	if (!(img->data))
		return (0);
	img = &ceil->img[1];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx, "textures/wood.xpm",
										&img->img_width, &img->img_height);
	if (!(img->img_ptr))
		return (0);
	img->data = (int*)mlx_get_data_addr(img->img_ptr, &img->bpp,
										&img->size_l, &img->endian);
	if (!(img->data))
		return (0);
	return (1);
}

void		draw_floor(t_game *game, t_ceil *ceil, int y)
{
	int		x;
	int		color;
	t_point	tex;

	x = 0;
	while (x < game->width)
	{
		ceil->cell.x = (int)(ceil->floor.x);
		ceil->cell.y = (int)(ceil->floor.y);
		tex.x = (int)(ceil->img[0].img_width * (ceil->floor.x
			- ceil->cell.x)) & (ceil->img[0].img_width - 1);
		tex.y = (int)(ceil->img[0].img_height * (ceil->floor.y
			- ceil->cell.y)) & (ceil->img[0].img_height - 1);
		ceil->floor.x += ceil->floor_step.x;
		ceil->floor.y += ceil->floor_step.y;
		color = ceil->img[0].data[(int)(ceil->img[0].size_l / 4
			* tex.y + tex.x)];
		game->buf[y][x] = color;
		color = ceil->img[1].data[(int)(ceil->img[1].size_l / 4
			* tex.y + tex.x)];
		game->buf[game->height - y - 1][x] = color;
		x++;
	}
}

void		floor_casting(t_game *game)
{
	int		y;
	t_ceil	ceil;

	y = 0;
	if (!get_tex_ceiling(game, &ceil))
		return ;
	while (y < game->height)
	{
		ceil.raydir_0.x = game->player.dir.x - game->player.plain.x;
		ceil.raydir_0.y = game->player.dir.y - game->player.plain.y;
		ceil.raydir_1.x = game->player.dir.x + game->player.plain.x;
		ceil.raydir_1.y = game->player.dir.y + game->player.plain.y;
		ceil.p = y - game->height / 2;
		ceil.pos_z = 0.5 * game->height;
		ceil.row_dist = ceil.pos_z / ceil.p;
		ceil.floor_step.x = ceil.row_dist *
			(ceil.raydir_1.x - ceil.raydir_0.x) / game->width;
		ceil.floor_step.y = ceil.row_dist *
			(ceil.raydir_1.y - ceil.raydir_0.y) / game->width;
		ceil.floor.x = game->player.pos.x + ceil.row_dist * ceil.raydir_0.x;
		ceil.floor.y = game->player.pos.y + ceil.row_dist * ceil.raydir_0.y;
		draw_floor(game, &ceil, y);
		y++;
	}
}
