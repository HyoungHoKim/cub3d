/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:57:18 by hhk               #+#    #+#             */
/*   Updated: 2021/03/09 13:49:29 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*gnl_strjoin(char *s1, char *s2)
{
	char			*temp;
	int				totalsize;
	int				idx;
	int				i;

	if (!s1 && !s2)
		return (0);
	totalsize = 0;
	idx = 0;
	i = 0;
	totalsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(temp = (char *)malloc(sizeof(char) * totalsize)))
		return (0);
	while (s1[idx] != '\0')
	{
		temp[idx] = s1[idx];
		idx++;
	}
	while (s2[i] != '\0')
		temp[idx++] = s2[i++];
	temp[totalsize - 1] = '\0';
	free(s1);
	return (temp);
}

int					gnl_strchr(const char *s)
{
	int				idx;
	int				len;

	idx = 0;
	len = ft_strlen(s);
	while (idx < len)
	{
		if (s[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

int					get_one_line(char **backup, char **line, int pos)
{
	char			*temp;

	*line = ft_substr(*backup, 0, pos);
	if ((ft_strlen(*backup) - (pos + 1)) == 0)
	{
		free(*backup);
		*backup = NULL;
		return (1);
	}
	temp = ft_substr(*backup, pos + 1, ft_strlen(*backup));
	free(*backup);
	*backup = temp;
	return (1);
}

int					clear_backup(char **backup, char **line, int read_size)
{
	int				pos;

	if (read_size < 0)
		return (-1);
	if (*backup && ((pos = gnl_strchr(*backup)) >= 0))
		return (get_one_line(backup, line, pos));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*backup[MAX_FILES];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	int				pos;

	if (BUFFER_SIZE <= 0 || !line || fd < 0)
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (!(backup[fd]))
			backup[fd] = ft_strdup(buf);
		else
			backup[fd] = gnl_strjoin(backup[fd], buf);
		if ((pos = gnl_strchr(backup[fd])) >= 0)
			return (get_one_line(&backup[fd], line, pos));
	}
	return (clear_backup(&backup[fd], line, read_size));
}
