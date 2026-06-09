/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 10:04:06 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 16:03:27 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	plus;
	int	space;
	int	hash;
	int	width;
	int	precision;
}	t_flags;

int		ft_printf(const char *format, ...);
int		handle_format(const char **format, va_list *args);
int		print_char(int c, t_flags f);
int		print_str(char *str, t_flags f);
int		print_int(int n, t_flags f);
int		print_uint(unsigned int n, t_flags f);
int		print_hex(unsigned int n, int uppercase, t_flags f);
int		print_ptr(void *ptr, t_flags f);
void	print_padding(int n, char c);
void	print_digits_int(int n);
int		count_digits(int n);
void	print_sign(int n, t_flags f);
int		print_intmin(t_flags f);
t_flags	parse_flags(const char **format, va_list *args);

#endif
