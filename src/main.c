/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/25 04:52:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

int	main(int ac, char const **av, char **envp)
{
	char	*dst;
	char	*buff;
	int		fd;

	(void)ac;
	// (void)av;
	// (void)envp;
	// if (ac < 5)
	// 	return (0);
	dst = check_program_exist((char *)av[1], envp);
	if (dst)
		ft_printf("%s\n", dst);
	fd = open(av[2], O_RDONLY);
	buff = get_next_line(fd);
	buff = get_next_line(fd);
	buff = get_next_line(fd);
	ft_printf("%s", buff);
	// dst = get_next_line(1);
	// ft_printf("%s", dst);
	// execve(dst, (char *const *)(av + 2), envp);
	return (0);
}
