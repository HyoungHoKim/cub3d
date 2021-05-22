# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 21:22:14 by hhk               #+#    #+#              #
#    Updated: 2021/02/04 00:00:06 by hyoukim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		= 	-Wall -Werror -Wextra
LIBFT		=	../libft
LIBFT_LIB	=	libft.a		
NAME 		=	libftprintf.a
SRCS 		= 	ft_printf.c addition_func.c\
				ft_initial_option.c \
				ft_print_by_type1.c ft_print_by_type2.c ft_print_by_type3.c ft_print_by_type4.c \
				ft_print_by_type_bonus1.c ft_print_by_type_bonus2.c addition_func_bonus.c
OBJS 		= 	$(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus : all

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY : all clean fclean re
