/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:20:09 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 15:24:03 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	read_flags(const char **format, t_flags *f)
{
	while (**format == '-' || **format == '0' || **format == '+'
		|| **format == ' ' || **format == '#')
	{
		if (**format == '-')
			f->minus = 1;
		else if (**format == '0')
			f->zero = 1;
		else if (**format == '+')
			f->plus = 1;
		else if (**format == ' ')
			f->space = 1;
		else if (**format == '#')
			f->hash = 1;
		(*format)++;
	}
}

static void	read_width(const char **format, t_flags *f, va_list *args)
{
	if (**format == '*')
	{
		f->width = va_arg(*args, int);
		(*format)++;
	}
	else
	{
		while (**format >= '0' && **format <= '9')
		{
			f->width = f->width * 10 + (**format - '0');
			(*format)++;
		}
	}
}

static void	read_precision(const char **format, t_flags *f, va_list *args)
{
	if (**format != '.')
		return ;
	(*format)++;
	f->precision = 0;
	if (**format == '*')
	{
		f->precision = va_arg(*args, int);
		(*format)++;
	}
	else
	{
		while (**format >= '0' && **format <= '9')
		{
			f->precision = f->precision * 10 + (**format - '0');
			(*format)++;
		}
	}
}

t_flags	parse_flags(const char **format, va_list *args)
{
	t_flags	f;

	f.minus = 0;
	f.zero = 0;
	f.plus = 0;
	f.space = 0;
	f.hash = 0;
	f.width = 0;
	f.precision = -1;
	read_flags(format, &f);
	read_width(format, &f, args);
	read_precision(format, &f, args);
	return (f);
}
