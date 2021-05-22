/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:21:12 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/13 22:12:56 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char		*check_line(t_game *game, char *line)
{
	int		len;
	char	*temp;

	len = 0;
	temp = line;
	while (*temp != '\0')
	{
		if (*temp == ' ' || *temp == '0' || *temp == '1' || *temp == '2'
		|| *temp == 'N' || *temp == 'S' || *temp == 'E' || *temp == 'W')
			len++;
		else
		{
			if (line != NULL)
				free(line);
			return (NULL);
		}
		temp++;
	}
	return (change_line(game, line, temp, len));
}

int			save_map_arr(t_game *game, t_list *temp)
{
	int		idx;
	int		len;

	if (!(game->map = (char**)malloc(sizeof(char*) * game->rows)))
		return (0);
	idx = 0;
	while (temp)
	{
		len = ft_strlen(temp->content);
		if (!(game->map[idx] = (char*)malloc(sizeof(char) * len + 1)))
			return (0);
		ft_strlcpy(game->map[idx], temp->content, len + 1);
		idx++;
		temp = temp->next;
	}
	return (1);
}

int			set_lst_map(t_game *game, int fd, char *line, t_list **temp_map)
{
	char	*temp;

	temp = NULL;
	if (!(temp = check_line(game, line)))
		return (0);
	*temp_map = ft_lstnew(temp);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(temp = check_line(game, line)))
		{
			ft_lstclear(temp_map, free);
			return (0);
		}
		ft_lstadd_back(temp_map, ft_lstnew(temp));
	}
	if (!(temp = check_line(game, line)))
	{
		ft_lstclear(temp_map, free);
		return (0);
	}
	ft_lstadd_back(temp_map, ft_lstnew(temp));
	game->rows = ft_lstsize(*temp_map);
	return (1);
}

int			save_map(t_game *game, int fd, char *line)
{
	int		idx;
	t_list	*temp_map;

	idx = 0;
	temp_map = NULL;
	if (!set_lst_map(game, fd, line, &temp_map))
		return (0);
	if (!save_map_arr(game, temp_map))
		return (0);
	ft_lstclear(&temp_map, free);
	return (1);
}

int			read_map(t_game *game, int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(check_map(game, line)))
			break ;
	}
	if (!save_map(game, fd, line))
		return (0);
	if (!init_check_map(game))
		return (0);
	game->x_tiles = game->width / game->cols;
	game->y_tiles = game->height / game->rows;
	return (1);
}
