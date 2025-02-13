/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:08:16 by julien            #+#    #+#             */
/*   Updated: 2024/11/29 11:53:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_format_arg(const char format, int *count_ptr, va_list args);
void	ft_putchar_count(const int c, int *count_ptr);
void	ft_putstr_count(const char *str, int *count_ptr);
void	ft_puthexbase_count(const unsigned long n, int *count_ptr,
			const char *base);
void	ft_puthex_count(const unsigned long n,
			int *count_ptr, const char format_base);
void	ft_putptr_count(const void *ptr, int *count_ptr);
void	ft_putdec_count(int n, int *count_ptr);
void	ft_putunsigned_count(const unsigned int n, int *count_ptr);

#endif
