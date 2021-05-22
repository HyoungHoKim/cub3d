/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:38:40 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/12 21:33:40 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		copy_test_map(t_game *game, char **test_map, int cols, int rows)
{
	int		x;
	int		y;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols && game->map[y][x] != '\0')
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'E'
			|| game->map[y][x] == 'W' || game->map[y][x] == 'S')
				test_map[y + 1][x + 1] = '0';
			else
				test_map[y + 1][x + 1] = game->map[y][x];
			x++;
		}
		y++;
	}
}

void		check_cols_invalid(char **test_map, int x, int y, int *match)
{
	if (ft_strncmp(&test_map[y][x], " 1", 2) == 0)
		*match = 0;
	else if (*match == 0 && test_map[y][x] == ' ' &&
		!(ft_strncmp(&test_map[y][x], " 1", 2) == 0))
		*match = 2;
	else if (ft_strncmp(&test_map[y][x], "1 ", 2) == 0
		&& *match == 0)
		*match = 1;
	else if (*match == 1 && ((test_map[y][x] == '0')
		|| (test_map[y][x] == '2')))
		*match = 2;
}
