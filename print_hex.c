/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 12:33:25 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/04 10:04:09 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_hex_digits(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static void	print_digits(unsigned int n, char *base)
{
	if (n >= 16)
		print_digits(n / 16, base);
	write(1, &base[n % 16], 1);
}

static void	print_hex_content(unsigned int n, int up, t_flags f, int padding)
{
	char	*base;

	if (up)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (!f.minus && !(f.zero && f.precision < 0))
		print_padding(padding, ' ');
	if (f.hash && n != 0)
	{
		if (up)
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
	if (!f.minus && f.zero && f.precision < 0)
		print_padding(padding, '0');
	if (f.precision > (int)count_hex_digits(n))
		print_padding(f.precision - count_hex_digits(n), '0');
	print_digits(n, base);
	if (f.minus)
		print_padding(padding, ' ');
}

int	print_hex(unsigned int n, int uppercase, t_flags f)
{
	int	digits;
	int	len;
	int	padding;

	digits = count_hex_digits(n);
	len = digits;
	if (f.precision > digits)
		len = f.precision;
	if (f.hash && n != 0)
		len += 2;
	if (f.precision == 0 && n == 0)
		len = 0;
	padding = f.width - len;
	if (f.precision == 0 && n == 0)
	{
		print_padding(padding, ' ');
		if (f.width > 0)
			return (f.width);
		return (0);
	}
	print_hex_content(n, uppercase, f, padding);
	if (f.width > len)
		return (f.width);
	return (len);
}
