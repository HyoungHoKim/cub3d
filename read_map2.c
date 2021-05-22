/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:19:38 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 15:03:54 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char		*change_line(t_game *game, char *line, char *temp, int len)
{
	int		max;
	char	*save_l;

	max = 0;
	save_l = line;
	if (!(temp = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_memset(temp, ' ', len);
	len = 0;
	while (*line != '\0')
	{
		if (*line == '\t')
			len += 4;
		else
			temp[len++] = *line;
		line++;
	}
	temp[len] = '\0';
	free(save_l);
	if (game->cols < len)
		game->cols = len;
	return (temp);
}

int			check_render_line(char **str)
{
	int		idx;
	char	**temp;

	temp = str;
	while (*str != 0)
	{
		idx = 0;
		while ((*str)[idx] != '\0')
		{
			if (ft_isdigit((*str)[idx]) || (*str)[idx] == ' ')
				idx++;
			else
			{
				free_split_arr(temp);
				return (0);
			}
		}
		str++;
	}
	return (1);
}

int			set_render_data(t_game *game, char **str)
{
	char	**temp;

	temp = str;
	while (*temp != 0)
	{
		if (ft_atoi(*temp) != 0 && game->width == -1 && game->height == -1)
			game->width = ft_atoi(*temp);
		else if (ft_atoi(*temp) != 0 && game->width != -1 && game->height == -1)
			game->height = ft_atoi(*temp);
		else if (ft_atoi(*temp) != 0 && game->width != -1 && game->height != -1)
		{
			free_split_arr(str);
			return (0);
		}
		temp++;
	}
	max_window_size(game);
	return (1);
}

int			init_render_size(t_game *game, char *line)
{
	char	**str;

	if (game->width != -1 && game->height != -1)
		return (0);
	if (!(str = ft_split(line + 2, ' ')))
		return (0);
	if (!check_render_line(str))
		return (0);
	if (!set_render_data(game, str))
		return (0);
	if (game->width <= 0 || game->height <= 0)
	{
		free_split_arr(str);
		return (0);
	}
	free_split_arr(str);
	free(line);
	return (1);
}

int			init_tex_path(t_game *game, char *line)
{
	if (ft_strncmp("NO", line, 2) == 0)
		return (get_tex_path(&game->tex_path[0], line, 3));
	else if (ft_strncmp("SO", line, 2) == 0)
		return (get_tex_path(&game->tex_path[1], line, 3));
	else if (ft_strncmp("WE", line, 2) == 0)
		return (get_tex_path(&game->tex_path[2], line, 3));
	else if (ft_strncmp("EA", line, 2) == 0)
		return (get_tex_path(&game->tex_path[3], line, 3));
	else if (ft_strncmp("S ", line, 2) == 0)
		return (get_tex_path(&game->sprite.path, line, 2));
	else
		return (0);
	return (1);
}
