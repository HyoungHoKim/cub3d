/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:51:14 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 18:18:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			main_loop(t_game *game)
{
	if (!ray_caster(game))
		return (print_error_message(game));
	if (game->game_mode == 2)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

int			map_2d(t_game *game)
{
	if (!window_init(game))
		return (0);
	img_init(game);
	if (!load_texture(game))
		return (0);
	if (game->game_mode == 1)
		return (screenshot(game));
	mlx_hook(game->win, X_EVENT_KEY_PRESS, 0, &deal_key, game);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, 0, &map_close, game);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_loop(game->mlx);
	return (1);
}

int			check_filename(int argc, char **argv,
						bool *is_save, char **filename)
{
	int size;

	if (argc < 2 || argc > 3)
		return (0);
	else if (argc == 3)
	{
		size = ft_strlen(argv[2]);
		if (size > 6)
			return (0);
		if (ft_strncmp("--save", argv[2], 6) == 0)
			*is_save = 1;
		else
			return (0);
	}
	*filename = argv[1];
	if (ft_strncmp(*filename + ft_strlen(*filename) - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	char	*filename;
	bool	is_save;
	t_game	*game;
	int		fd;

	is_save = 0;
	filename = NULL;
	game = NULL;
	if (!check_filename(argc, argv, &is_save, &filename))
		return (print_error_message(game));
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (print_error_message(game));
	if (!(game = game_init(is_save)))
		return (print_error_message(game));
	game->mlx = mlx_init();
	if (!read_map(game, fd))
		return (print_error_message(game));
	if (!map_2d(game))
		return (print_error_message(game));
	return (0);
}
