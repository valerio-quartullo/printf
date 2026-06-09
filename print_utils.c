/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:56:07 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/04 15:56:30 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_padding(int n, char c)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}

void	print_digits_int(int n)
{
	char	c;

	if (n >= 10)
		print_digits_int(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	count_digits(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void	print_sign(int n, t_flags f)
{
	if (n < 0)
		write(1, "-", 1);
	else if (f.plus)
		write(1, "+", 1);
	else if (f.space)
		write(1, " ", 1);
}

int	print_intmin(t_flags f)
{
	int	padding;
	int	printed;

	printed = 0;
	padding = f.width - 11;
	if (padding < 0)
		padding = 0;
	if (!f.minus)
	{
		print_padding(padding, ' ');
		printed += padding;
	}
	write(1, "-2147483648", 11);
	printed += 11;
	if (f.minus)
	{
		print_padding(padding, ' ');
		printed += padding;
	}
	return (printed);
}
