/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:48:27 by itan              #+#    #+#             */
/*   Updated: 2023/02/26 01:55:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**lst_join(char **a, char **b)
{
	char	**dst;
	int		l_a;
	int		l_b;
	int		i;

	l_a = 0;
	l_b = 0;
	while (a[l_a])
		l_a++;
	while (b[l_b])
		l_b++;
	dst = (char **)ft_calloc(l_a + l_b + 1, sizeof(char *));
	if (!dst)
		return (0);
	i = 0;
	while (*a)
		dst[i++] = *(a++);
	while (*b)
		dst[i++] = *(b++);
	return (dst);
}
