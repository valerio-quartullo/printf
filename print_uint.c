/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 12:00:25 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 16:11:37 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_udigits(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	print_udigits(unsigned int n)
{
	char	c;

	if (n >= 10)
		print_udigits(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	print_uint(unsigned int n, t_flags f)
{
	int	digits;
	int	prec_pad;
	int	len;

	digits = count_udigits(n);
	if (f.precision == 0 && n == 0)
		digits = 0;
	prec_pad = 0;
	if (f.precision > digits)
		prec_pad = f.precision - digits;
	len = digits + prec_pad;
	if (!f.minus && !(f.zero && f.precision < 0))
		print_padding(f.width - len, ' ');
	if (!f.minus && f.zero && f.precision < 0)
		print_padding(f.width - len, '0');
	print_padding(prec_pad, '0');
	if (!(f.precision == 0 && n == 0))
		print_udigits(n);
	if (f.minus)
		print_padding(f.width - len, ' ');
	if (f.width > len)
		return (f.width);
	return (len);
}
