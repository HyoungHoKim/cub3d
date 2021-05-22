/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:25:09 by hhk               #+#    #+#             */
/*   Updated: 2021/02/03 23:59:06 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>
# include "../libft/libft.h"

typedef struct	s_option
{
	bool		is_minus;
	bool		is_zero;
	int			width;
	int			precision;
	char		type;
}				t_option;

int				ft_printf(const char *format, ...);
int				ft_initial_option(const char *format, va_list ap,
								int pos, t_option **save);
int				ft_print_char(va_list ap, t_option *save);
int				ft_print_string(va_list ap, t_option *save);
int				ft_print_string_width(char *str, t_option *save);
int				ft_print_pointer(va_list ap, t_option *save);
int				ft_print_x(va_list ap, t_option *save);
char			*ft_print_x_precision(char *str, t_option *save);
char			*ft_print_x_width(char *str, t_option *save);
int				ft_print_di(va_list ap, t_option *save);
char			*ft_print_di_width(char *str, t_option *save);
int				ft_print_u(va_list ap, t_option *save);
int				ft_print_percent(t_option *save);

char			*utoa(unsigned long long address);
char			*ft_uitoa(unsigned int n);

void			ft_print_n(va_list ap, int len);
int				ft_print_f(va_list ap, t_option *save);
char			*ft_print_f_decimal(double num, uint64_t dec,
									t_option *save, bool is_minus);

bool			is_denormalized(double num, bool *is_minus);
char			*ft_maxitoa(intmax_t n);
intmax_t		ft_round(double f);

#endif
