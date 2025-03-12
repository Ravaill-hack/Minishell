/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:05:42 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/12 10:37:21 by Lmatkows         ###   ########.fr       */
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
	long long	result;

	result = 0;
	if (ft_strlen(nptr) > 20)
		return (-1);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		return (-2);
	if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		if (result > (9223372036854775807LL / 10)
			|| (result == 9223372036854775807LL / 10 && (*nptr - '0') > 7))
			return (-1);
		result = (result * (long long)10) + (*nptr - 48);
		nptr++;
	}
	if (*nptr != '\0' || result > 9223372036854775807LL)
		return (-1);
	return ((long)result);
}
