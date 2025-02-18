/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:01:54 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 11:12:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		ft_putstr_fd(strs[i], 1);
        ft_putchar_fd('\n', 1);
		i++;
	}
}