/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:42:02 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/11 13:22:13 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			check_invalid_rgb(int *color)
{
	int		idx;

	idx = 0;
	while (idx < 3)
	{
		if (color[idx] < 0 || color[idx] > 255)
			return (0);
		idx++;
	}
	return (1);
}

int			check_comma_num(char *line)
{
	int		num;
	int		idx;

	num = 0;
	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == ',')
			num++;
		idx++;
	}
	if (num == 2)
		return (1);
	return (0);
}

int			init_floor_ceil_rgb(t_game *game, char *line)
{
	char	**rgb;
	int		color[3];

	if (!check_comma_num(line))
		return (0);
	color[0] = -1;
	color[1] = -1;
	color[2] = -1;
	if (!(rgb = ft_split(line + 2, ',')))
		return (0);
	if (!check_render_line(rgb))
		return (0);
	if (ft_strncmp("F ", line, 2) == 0)
		game->background[1] = get_color_map(rgb, color);
	else if (ft_strncmp("C ", line, 2) == 0)
		game->background[0] = get_color_map(rgb, color);
	free_split_arr(rgb);
	free(line);
	return (1);
}

int			get_color_map(char **rgb, int *color)
{
	char	**temp;

	temp = rgb;
	while (*temp != 0)
	{
		if (color[0] == -1 && color[1] == -1 && color[2] == -1)
			color[0] = ft_atoi(*temp);
		else if (color[0] != -1 && color[1] == -1 && color[2] == -1)
			color[1] = ft_atoi(*temp);
		else if (color[0] != -1 && color[1] != -1 && color[2] == -1)
			color[2] = ft_atoi(*temp);
		else
			return (-1);
		temp++;
	}
	if (!check_invalid_rgb(color))
		return (-1);
	return (color[0] << 16) | (color[1] << 8) | color[2];
}

void		set_dir_plain(t_game *game, char c)
{
	if (c == 'N')
	{
		set_point(&game->player.dir, 0, -1);
		set_point(&game->player.plain, -0.66, 0);
	}
	else if (c == 'S')
	{
		set_point(&game->player.dir, 0, 1);
		set_point(&game->player.plain, 0.66, 0);
	}
	else if (c == 'E')
	{
		set_point(&game->player.dir, 1, 0);
		set_point(&game->player.plain, 0, -0.66);
	}
	else if (c == 'W')
	{
		set_point(&game->player.dir, -1, 0);
		set_point(&game->player.plain, 0, 0.66);
	}
}
