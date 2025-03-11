/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:05:42 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/11 12:46:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// convert a string to a long

// DESCRIPTION :
// The ft_atol() function converts the initial portion of the string
// in nptr to a long value
// The string may begin with an arbitrary amount of white space
// (as determined by isspace()
// followed by a single optional '+' or '-' sign
// The remainder of the string is converted to an int value
// in the obvious manner,
// stopping at the first character which is not a valid digit
// If there were no digits at all, ft_atol() returns 0)

// Note : ft_atol() does not detect errors

// RETURN VALUE :
// The ft_atol() function returns the result of the conversion,
// unless the value would underflow or overflow.
long	ft_atol(const char *nptr)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (ft_isspace((int)*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit((int)*nptr))
	{
		result = (result * 10) + ((int)(*nptr) - 48);
		nptr++;
	}
	return (sign * result);
}
