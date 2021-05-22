/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:00:07 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/07 18:51:04 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			get_image_data(t_game *game, int idx)
{
	t_img	*img;

	img = &game->tex[idx];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx, game->tex_path[idx],
										&img->img_width, &img->img_height);
	if (!(img->img_ptr))
		return (0);
	img->data = (int*)mlx_get_data_addr(img->img_ptr, &img->bpp,
										&img->size_l, &img->endian);
	if (!(img->data))
		return (0);
	return (1);
}

int			init_texture(t_game *game)
{
	int		idx;

	game->buf = (int**)malloc(sizeof(int*) * game->height);
	if (!game->buf)
		return (0);
	idx = 0;
	while (idx < game->height)
	{
		game->buf[idx] = (int*)malloc(sizeof(int) * game->width);
		if (!game->buf[idx])
			return (0);
		idx++;
	}
	return (1);
}

int			load_texture(t_game *game)
{
	int		idx;

	if (!init_texture(game))
		return (0);
	idx = 0;
	while (idx < 4)
	{
		if (!get_image_data(game, idx))
			return (0);
		idx++;
	}
	return (1);
}
