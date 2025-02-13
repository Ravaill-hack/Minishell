/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:04:22 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/13 08:37:31 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// checks for white-space characters.
// In "C" these are: space, form-feed ('\f'), newline ('\n'),
// carriage return ('\r'), horizontal tab  ('\t'), 
// and  vertical tab ('\v')
int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
