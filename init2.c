/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:34:11 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/13 18:17:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			get_sprite_data(t_game *game)
{
	t_img	*img;

	img = game->sprite.img;
	img->img_ptr = mlx_xpm_file_to_image(game->mlx, img->path,
										&img->img_width, &img->img_height);
	if (!(img->img_ptr))
		return (0);
	img->data = (int*)mlx_get_data_addr(img->img_ptr, &img->bpp,
										&img->size_l, &img->endian);
	if (!(img->data))
		return (0);
	return (1);
}

int			set_memory_sprite(t_game *game, int num)
{
	game->z_buf = (double*)malloc(sizeof(double) * game->width);
	if (!game->z_buf)
		return (0);
	game->sprite.img = (t_img*)malloc(sizeof(t_img));
	game->sprite.img->path = game->sprite.path;
	if (!game->sprite.img)
		return (0);
	if (!get_sprite_data(game))
		return (0);
	game->sprite.pos = (t_point*)malloc(sizeof(t_point) * num);
	if (!game->sprite.pos)
		return (0);
	game->sprite.s_order = (int*)malloc(sizeof(int) * num);
	if (!game->sprite.s_order)
		return (0);
	game->sprite.s_dist = (double*)malloc(sizeof(double) * num);
	if (!game->sprite.s_dist)
		return (0);
	return (1);
}

int			init_sprite(t_game *game)
{
	int		x;
	int		y;
	int		num;

	y = 0;
	get_sprite_num(game);
	num = game->sprite.num;
	if (!(set_memory_sprite(game, num)))
		return (0);
	num = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == '2')
				set_point(&(game->sprite.pos[num++]), 0.5 + x, 0.5 + y);
			x++;
		}
		y++;
	}
	return (1);
}

int			check_data_invalid(t_game *game)
{
	int		x;
	int		y;
	int		is_read;
	char	num;

	y = 0;
	is_read = 1;
	while (y < game->rows)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			num = game->map[y][x];
			if (num == '0' || num == 'N' || num == 'S' || num == 'E'
			|| num == 'W' || num == '0' || num == '1' || num == '2'
			|| num == ' ')
				x++;
			else
				return (0);
		}
		y++;
	}
	return (is_read);
}

int			init_check_map(t_game *game)
{
	if (!check_data_invalid(game))
		return (0);
	if (!init_player(game))
		return (0);
	if (game->player.pos.x == -1 || game->player.pos.y == -1)
		return (0);
	if (!check_valid_map(game))
		return (0);
	if (!init_sprite(game))
		return (0);
	return (1);
}
