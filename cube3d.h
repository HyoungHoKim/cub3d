/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:27:05 by hyoukim           #+#    #+#             */
/*   Updated: 2021/03/14 22:36:01 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE			6
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_M					46
# define KEY_LEFT				123
# define KEY_RIGHT				124

# define TEX_WIDTH				64
# define TEX_HEIGHT				64

typedef	struct					s_point
{
	double						x;
	double						y;
}								t_point;

typedef	struct					s_dda
{
	t_point						r_dir;
	t_point						map;
	t_point						s_dist;
	t_point						d_dist;
	t_point						step;
	int							side;

	double						perpwalldist;
	int							line_h;
	int							draw_start;
	int							draw_end;
	int							color;
}								t_dda;

typedef	struct					s_s_draw
{
	t_point						s_pos;
	double						inv_det;
	t_point						transform;
	int							s_screen_x;
	int							s_height;
	int							s_width;
	t_point						draw_start;
	t_point						draw_end;
	int							st;
	t_point						tex;
}								t_s_draw;

typedef struct					s_player
{
	t_point						pos;
	t_point						dir;
	double						move_speed;
	double						rot_speed;
	t_point						plain;
}								t_player;

typedef	struct					s_img
{
	void						*img_ptr;
	int							*data;
	int							size_l;
	int							bpp;
	int							endian;
	char						*path;
	int							img_width;
	int							img_height;
}								t_img;

typedef struct					s_sprite
{
	char						*path;
	t_img						*img;
	int							num;
	t_point						*pos;
	int							*s_order;
	double						*s_dist;
}								t_sprite;

typedef	struct					s_game
{
	void						*mlx;
	void						*win;

	t_img						img;
	char						*tex_path[4];
	t_img						tex[4];
	int							**buf;
	int							background[2];
	double						*z_buf;
	t_sprite					sprite;

	int							width;
	int							height;
	int							cols;
	int							rows;
	int							x_tiles;
	int							y_tiles;
	char						**map;

	t_player					player;
	t_point						old_mouse_pos;
	t_point						new_mouse_pos;
	int							game_mode;
}								t_game;

typedef struct					s_ceil
{
	t_point						raydir_0;
	t_point						raydir_1;
	int							p;
	float						pos_z;
	float						row_dist;
	t_point						floor_step;
	t_point						floor;
	t_point						cell;

	t_img						img[2];
}								t_ceil;

void							draw_ray(t_game *game);
int								read_map(t_game *game, int fd);
char							*change_line(t_game *game, char *line,
											char *temp, int len);
t_game							*game_init(bool is_save);
int								window_init(t_game *game);
void							img_init(t_game *game);
int								print_error_message(t_game *game);
int								init_tex_path(t_game *game, char *line);
void							reinit_img(t_game *game);
int								init_render_size(t_game *game, char *line);
int								check_render_line(char **str);
int								init_check_map(t_game *game);
int								init_player(t_game *game);
int								save_player_origin(t_game *game, char c,
													int x, int y);
void							set_dir_plain(t_game *game, char c);
int								check_valid_map(t_game *game);
int								load_texture(t_game *game);
int								deal_key(int key_code, t_game *game);
void							init_dda(t_game *game, t_dda *dda,
										double camera_x);
int								ray_dda(t_game *game, t_dda *dda);
int								ray_caster(t_game *game);
void							set_textures(t_game *game, t_dda dda, int x);
void							image_draw(t_game *game);
int								set_default_bg(t_game *game, int x);
void							print_map(char **map, int rows);
void							set_point(t_point *pos, double x, double y);
int								get_tex_path(char **tex_path,
										char *line, int pos);
int								init_floor_ceil_rgb(t_game *game, char *line);
int								get_color_map(char **rgb, int *color);
void							free_split_arr(char **arr);
void							copy_test_map(t_game *game, char **test_map,
												int cols, int rows);
void							draw_sprite(t_game *game);
void							get_sprite_num(t_game *game);
void							sort_sprites(t_game *game);
void							set_sprite_color_y(t_game *game,
											t_s_draw *s_d, t_point *st);
int								save_image_to_bmp(int **data,
												int width, int height);
void							free_t_game(t_game *game);
char							**init_test_map(t_game *game);
void							set_dir_plain(t_game *game, char c);
void							init_player_data(t_game *game);
int								check_map(t_game *game, char *line);
void							move_left(t_game *game);
void							move_right(t_game *game);
void							check_cols_invalid(char **test_map,
											int x, int y, int *match);
int								screenshot(t_game *game);
int								map_close(t_game *game);
void							rot_right(t_game *game);
void							rot_left(t_game *game);
void							max_window_size(t_game *game);

void							draw_rectangles(t_game *game);
void							draw_player_pos(t_game *game);
void							draw_minimap(t_game *game);
void							floor_casting(t_game *game);

#endif
