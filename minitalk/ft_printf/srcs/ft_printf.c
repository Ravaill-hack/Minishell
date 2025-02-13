/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:36:35 by sakamoto-42       #+#    #+#             */
/*   Updated: 2024/11/29 11:45:17 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_arg(const char format, int *count_ptr, va_list args)
{
	if (format == 'c')
		ft_putchar_count(va_arg(args, const int), count_ptr);
	else if (format == 's')
		ft_putstr_count(va_arg(args, const char *), count_ptr);
	else if (format == 'p')
		ft_putptr_count(va_arg(args, const void *), count_ptr);
	else if (format == 'd' || format == 'i')
		ft_putdec_count(va_arg(args, int), count_ptr);
	else if (format == 'u')
		ft_putunsigned_count(va_arg(args, const unsigned int), count_ptr);
	else if (format == 'x' || format == 'X')
		ft_puthex_count(va_arg(args, const unsigned int), count_ptr, format);
	else if (format == '%')
		ft_putchar_count('%', count_ptr);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format_arg(*str, &count, args);
		}
		else
			ft_putchar_count(*str, &count);
		str++;
	}
	va_end(args);
	return (count);
}
