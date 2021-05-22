/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:38:40 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/12 21:30:22 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			test_map_cols(char **test_map, int rows, int cols)
{
	int		x;
	int		y;
	int		match;

	y = 1;
	while (y < rows - 1)
	{
		x = 0;
		match = -1;
		while (x < cols - 1)
		{
			check_cols_invalid(test_map, x, y, &match);
			if (match == 2)
			{
				return (0);
			}
			x++;
		}
		if (match != 1)
			return (0);
		y++;
	}
	return (1);
}

void		check_rows_invalid(char **test_map, int x, int y, int *match)
{
	if (test_map[y][x] == ' ' && test_map[y + 1][x] == '1')
		*match = 0;
	else if (match == 0 && test_map[y][x] == ' ' &&
		!(test_map[y][x] == ' ' && test_map[y + 1][x] == '1'))
		*match = 2;
	else if ((test_map[y][x] == '1' &&
			test_map[y + 1][x] == ' ') && *match == 0)
		*match = 1;
	else if (*match == 1 && ((test_map[y][x] == '0')
		|| (test_map[y][x] == '2')))
		*match = 2;
}

int			test_map_rows(char **test_map, int rows, int cols)
{
	int		x;
	int		y;
	int		match;

	x = 1;
	while (x < cols - 1)
	{
		y = 0;
		match = -1;
		while (y < rows - 1)
		{
			check_rows_invalid(test_map, x, y, &match);
			if (match == 2)
			{
				return (0);
			}
			y++;
		}
		if (match != 1)
			return (0);
		x++;
	}
	return (1);
}

int			check_test_map(char **test_map, int rows, int cols)
{
	int		idx;

	idx = 0;
	if (!test_map_cols(test_map, rows, cols))
	{
		while (idx < rows)
			free(test_map[idx++]);
		free(test_map);
		return (0);
	}
	if (!test_map_rows(test_map, rows, cols))
	{
		idx = 0;
		while (idx < rows)
			free(test_map[idx++]);
		free(test_map);
		return (0);
	}
	return (1);
}

int			check_valid_map(t_game *game)
{
	char	**test_map;
	int		idx;

	test_map = NULL;
	if (!(test_map = init_test_map(game)))
		return (0);
	copy_test_map(game, test_map, game->cols, game->rows);
	if (!check_test_map(test_map, game->rows + 2, game->cols + 2))
		return (0);
	idx = 0;
	while (idx < game->rows + 2)
		free(test_map[idx++]);
	free(test_map);
	return (1);
}
