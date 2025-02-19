/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:42:41 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 17:00:13 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_quote_error(char *line)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0; // 1 = open quote ; 0 = closed quote
	nd = 0; // 1 = open quote ; 0 = closed quote
	while (line[i])
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (nd != 0 || ns != 0)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	printf("code erreur : %d\n", (ft_quote_error(argv[1])));
}