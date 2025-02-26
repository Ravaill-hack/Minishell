/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:44:55 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/26 14:47:05 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*ft_strjoin_n(int count, ...)
{
	va_list		args;
	char		*result;
	char		*temp;
	char		*next;

	if (count <= 0)
		return (NULL);
	va_start(args, count);
	result = va_arg(args, char *);
	if (!result)
		return (va_end(args), NULL);
	result = ft_strdup(result);
	count--;
	while (count > 0)
	{
		next = va_arg(args, char *);
		if (next)
		{
			temp = ft_strjoin(result, next);
			free(result);
			result = temp;
		}
		count--;
	}
	return (va_end(args), result);
}