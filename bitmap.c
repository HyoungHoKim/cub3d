/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:29:43 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/10 21:59:55 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_default_value(unsigned char header[])
{
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
}

void	set_header(unsigned char header[], int width,
				int height, int row_size)
{
	unsigned short	bitcount;
	unsigned int	img_size;
	unsigned int	filesize;

	bitcount = 24;
	img_size = row_size * height;
	filesize = 54 + img_size;
	set_default_value(header);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 18, &width, 4);
	ft_memcpy(header + 22, &height, 4);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &img_size, 4);
}

void	set_pixels(unsigned char *buf, int **data, int width, int height)
{
	unsigned int	row_size;
	int				i;
	int				j;
	int				tmp;

	row_size = ((width * 24 + 31) / 32) * 4;
	tmp = height;
	i = -1;
	while (++i < height)
	{
		j = 0;
		--tmp;
		while (++j < width)
		{
			buf[tmp * row_size + j * 3 + 0] = (data[i][(width - 1) - j]) & 0xff;
			buf[tmp * row_size + j * 3 + 1] =
					(data[i][(width - 1) - j] >> 8) & 0xff;
			buf[tmp * row_size + j * 3 + 2] =
					(data[i][(width - 1) - j] >> 16) & 0xff;
		}
	}
}

int		write_file(unsigned char header[], unsigned char *buf,
					unsigned int size)
{
	int fd;

	if ((fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, 0666)) == -1)
		return (0);
	write(fd, header, 54);
	write(fd, (char*)buf, size);
	close(fd);
	return (1);
}

int		save_image_to_bmp(int **data, int width, int height)
{
	unsigned char	header[54];
	unsigned char	*buf;
	unsigned int	row_size;
	unsigned int	pixel_arr_size;

	row_size = ((width * 24 + 31) / 32) * 4;
	pixel_arr_size = row_size * height;
	set_header(header, width, height, row_size);
	buf = malloc(pixel_arr_size);
	if (!buf)
		return (0);
	set_pixels(buf, data, width, height);
	if (!write_file(header, buf, pixel_arr_size))
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}
