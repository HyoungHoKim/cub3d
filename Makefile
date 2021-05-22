CC			= gcc
CFLAGS		= -g3 -O2 -Wall -Werror -Wextra -I.
MLX_LIB		= libmlx.dylib
LIBFT_LIB	= libft.a
FP_LIB		= libftprintf.a
GNL_LIB		= libgnl.a
LIB_FLAGS	= -L. -lmlx -framework OpenGL -framework AppKit \
			  -L. -lft \
			  -L. -lgnl \
		      -L. -lftprintf
SRCS		= cube3d.c draw_ray.c read_map.c read_map2.c \
			  deal_key.c raycaster.c init.c init2.c init3.c utils.c load_tex.c draw_wall.c \
			  draw_background.c check_valid_map.c read_map3.c check_valid_map2.c draw_sprite.c \
			  draw_sprite2.c bitmap.c utils2.c read_map4.c deal_key2.c bitmap2.c
SRCS_B		= draw_minimap_bonus.c tex_ceiling_bonus.c
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
NAME		= cub3D

all: $(NAME)

bonus : all

$(MLX_LIB):
	make -C mlx/
	mv mlx/$(MLX_LIB) .

$(LIBFT_LIB):
	make -C libft/
	mv libft/$(LIBFT_LIB) .

$(GNL_LIB):
	make -C gnl/
	mv gnl/$(GNL_LIB) .

$(FP_LIB):
	make -C ft_printf/
	mv ft_printf/$(FP_LIB) .


$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(GNL_LIB) $(FP_LIB) $(OBJS) $(OBJS_B)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJS_B) $(LIB_FLAGS) 

clean:
	rm -f $(OBJS) $(OBJS_B)
	make clean -C mlx/
	make clean -C gnl/
	make clean -C ft_printf/

fclean: clean 
	rm -f $(NAME) $(MLX_LIB) $(LIBFT_LIB) $(GNL_LIB) $(FP_LIB)

re: fclean all 

.PHONY: all clean fclean re

