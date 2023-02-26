/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/26 21:42:45 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

char	**get_commants(char const **av, int count)
{
	char	**dst;
	int		i;

	i = 0;
	dst = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (0);
	while (i < count)
	{
		dst[i] = ft_strdup((char *)(av + 2)[i]);
		i++;
	}
	return (dst);
}

void	print2d(char **val)
{
	while (*val)
		ft_printf("%s\n", *(val++));
}

int	main(int ac, char const **av, char **envp)
{
	t_pipex_data	data;

	if (ac < 5)
		return (1);
	data.fd_in = open(av[1], O_RDONLY);
	data.fd_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR);
	data.cmds = get_commants(av, ac - 3);
	data.recur_depth = 0;
	pipe(data.p_fd1);
	pipe(data.p_fd2);
	fork_recursion(&data, envp);
	return (0);
}
