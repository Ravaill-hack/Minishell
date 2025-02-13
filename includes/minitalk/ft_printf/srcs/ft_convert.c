/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:07:37 by julien            #+#    #+#             */
/*   Updated: 2024/11/29 11:56:49 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar_count(const int c, int *count_ptr)
{
	*count_ptr += write(1, &c, 1);
}

void	ft_putstr_count(const char *str, int *count_ptr)
{
	if (!str)
	{
		ft_putstr_count("(null)", count_ptr);
		return ;
	}
	while (*str)
	{
		ft_putchar_count((const int)*str, count_ptr);
		str++;
	}
}

void	ft_putptr_count(const void *ptr, int *count_ptr)
{
	if (!ptr)
	{
		ft_putstr_count("(nil)", count_ptr);
		return ;
	}
	ft_putstr_count("0x", count_ptr);
	ft_puthex_count((const unsigned long)ptr, count_ptr, 'x');
}

void	ft_putdec_count(int n, int *count_ptr)
{
	if (n == -2147483648)
	{
		ft_putstr_count("-2147483648", count_ptr);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_count((const int)('-'), count_ptr);
		n = -n;
	}
	if (n >= 10)
		ft_putdec_count(n / 10, count_ptr);
	ft_putchar_count(n % 10 + 48, count_ptr);
}

void	ft_putunsigned_count(const unsigned int n, int *count_ptr)
{
	if (n >= 10)
		ft_putunsigned_count(n / 10, count_ptr);
	ft_putchar_count((const int)(n % 10 + 48), count_ptr);
}
