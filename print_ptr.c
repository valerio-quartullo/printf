/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 12:45:06 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 16:00:44 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_hex_digits(unsigned long n)
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

static void	print_digits(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		print_digits(n / 16);
	write(1, &base[n % 16], 1);
}

static int	print_nil(t_flags f)
{
	int	padding;

	padding = f.width - 5;
	if (!f.minus)
		print_padding(padding, ' ');
	write(1, "(nil)", 5);
	if (f.minus)
		print_padding(padding, ' ');
	if (f.width > 5)
		return (f.width);
	return (5);
}

int	print_ptr(void *ptr, t_flags f)
{
	int	len;
	int	padding;

	if (!ptr)
		return (print_nil(f));
	len = count_hex_digits((unsigned long)ptr) + 2;
	padding = f.width - len;
	if (!f.minus)
		print_padding(padding, ' ');
	write(1, "0x", 2);
	print_digits((unsigned long)ptr);
	if (f.minus)
		print_padding(padding, ' ');
	if (f.width > len)
		return (f.width);
	return (len);
}
