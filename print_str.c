/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:12:27 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/08 15:37:13 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	str_len(char *str, t_flags f)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (f.precision >= 0 && f.precision < len)
		len = f.precision;
	return (len);
}

int	print_str(char *str, t_flags f)
{
	int	len;
	int	padding;

	if (!str && f.precision >= 0 && f.precision < 6)
		str = "";
	else if (!str)
		str = "(null)";
	len = str_len(str, f);
	padding = f.width - len;
	if (!f.minus)
		print_padding(padding, ' ');
	write(1, str, len);
	if (f.minus)
		print_padding(padding, ' ');
	if (f.width > len)
		return (f.width);
	return (len);
}
