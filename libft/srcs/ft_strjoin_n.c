/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:09:21 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 17:48:49 by lmatkows         ###   ########.fr       */
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
