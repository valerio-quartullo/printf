/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:28:07 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 15:59:44 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_zero_prec(int padding, int width)
{
	print_padding(padding, ' ');
	if (width > 0)
		return (width);
	return (0);
}

static void	print_int_body(int n, t_flags f, int padding, int prec_pad)
{
	if (!f.minus && !(f.zero && f.precision < 0))
		print_padding(padding, ' ');
	print_sign(n, f);
	if (f.zero && !f.minus && f.precision < 0)
		print_padding(padding, '0');
	print_padding(prec_pad, '0');
	if (n < 0)
		print_digits_int(-n);
	else
		print_digits_int(n);
	if (f.minus)
		print_padding(padding, ' ');
}

int	print_int(int n, t_flags f)
{
	int	digits;
	int	prec_pad;
	int	len;
	int	padding;

	if (n == -2147483648)
		return (print_intmin(f));
	digits = count_digits(n);
	prec_pad = 0;
	if (f.precision > digits)
		prec_pad = f.precision - digits;
	len = digits + prec_pad;
	if (n < 0 || f.plus || f.space)
		len++;
	if (f.precision == 0 && n == 0)
		return (handle_zero_prec(f.width, f.width));
	padding = f.width - len;
	print_int_body(n, f, padding, prec_pad);
	if (f.width > len)
		return (f.width);
	return (len);
}
