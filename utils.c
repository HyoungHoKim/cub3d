/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:28:06 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 23:09:30 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		print_map(char **map, int rows)
{
	int		i;
	int		j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		ft_printf("cols : %d, line : ", (int)ft_strlen(map[i]));
		while (j < (int)ft_strlen(map[i]))
		{
			ft_printf("%c", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void		set_point(t_point *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

int			get_tex_path(char **tex_path, char *line, int pos)
{
	char	*str;
	char	*temp;
	int		len;

	if (*tex_path != NULL)
		return (0);
	temp = line + pos;
	len = ft_strlen(temp);
	str = (char*)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, temp, len + 1);
	*tex_path = str;
	free(line);
	return (1);
}

void		free_split_arr(char **arr)
{
	int		idx;

	idx = 0;
	while (arr[idx] != 0)
	{
		free(arr[idx]);
		idx++;
	}
	free(arr);
}

int			print_error_message(t_game *game)
{
	ft_printf("Error\n");
	free_t_game(game);
	exit(0);
}
