/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:27:03 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/13 16:31:26 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		screenshot(t_game *game)
{
	if (!ray_caster(game))
		return (print_error_message(game));
	save_image_to_bmp(game->buf, game->width, game->height);
	free_t_game(game);
	return (1);
}
