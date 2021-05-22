/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:13:21 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/10 19:14:07 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			check_map(t_game *game, char *line)
{
	if (ft_memcmp(line, "R ", 2) == 0)
		return (init_render_size(game, line));
	else if (ft_memcmp(line, "NO", 2) == 0 || ft_memcmp(line, "SO", 2) == 0
			|| ft_memcmp(line, "WE", 2) == 0 || ft_memcmp(line, "EA", 2) == 0
			|| ft_memcmp(line, "S ", 2) == 0)
		return (init_tex_path(game, line));
	else if (ft_memcmp(line, "F ", 2) == 0 || ft_memcmp(line, "C ", 2) == 0)
		return (init_floor_ceil_rgb(game, line));
	else if (ft_strlen(line) == 0)
	{
		free(line);
		return (1);
	}
	else
		return (0);
}
