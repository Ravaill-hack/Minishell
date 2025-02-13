/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:50:25 by julien            #+#    #+#             */
/*   Updated: 2024/11/29 11:53:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexbase_count(const unsigned long n,
	int *count_ptr, const char *base)
{
	char	c;

	if (n >= 16)
		ft_puthexbase_count(n / 16, count_ptr, base);
	c = base[n % 16];
	ft_putchar_count((const int) c, count_ptr);
}

void	ft_puthex_count(const unsigned long n,
	int *count_ptr, const char format_base)
{
	if (format_base == 'x')
		ft_puthexbase_count(n, count_ptr, "0123456789abcdef");
	else if (format_base == 'X')
		ft_puthexbase_count(n, count_ptr, "0123456789ABCDEF");
}
