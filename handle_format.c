/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:55:53 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 15:22:30 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(const char **format, va_list *args)
{
	t_flags	f;

	f = parse_flags(format, args);
	if (**format == 'c')
		return (print_char(va_arg(*args, int), f));
	else if (**format == 's')
		return (print_str(va_arg(*args, char *), f));
	else if (**format == 'd' || **format == 'i')
		return (print_int(va_arg(*args, int), f));
	else if (**format == 'u')
		return (print_uint(va_arg(*args, unsigned int), f));
	else if (**format == 'x')
		return (print_hex(va_arg(*args, unsigned int), 0, f));
	else if (**format == 'X')
		return (print_hex(va_arg(*args, unsigned int), 1, f));
	else if (**format == 'p')
		return (print_ptr(va_arg(*args, void *), f));
	else if (**format == '%')
		return (write(1, "%", 1));
	return (0);
}
