/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/22 21:29:14 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char const **av)
{
	int	val;

	(void)(ac);
	(void)(av);
	val = access("/usr/bin/make", F_OK);
	ft_printf("$i", val);
	perror("");
	return (0);
}
