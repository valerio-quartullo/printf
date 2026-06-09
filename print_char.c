/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquartul <vquartul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:57:34 by vquartul          #+#    #+#             */
/*   Updated: 2026/06/03 15:57:45 by vquartul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c, t_flags f)
{
	int	padding;

	padding = f.width - 1;
	if (!f.minus)
		print_padding(padding, ' ');
	write(1, &c, 1);
	if (f.minus)
		print_padding(padding, ' ');
	if (f.width > 1)
		return (f.width);
	return (1);
}
