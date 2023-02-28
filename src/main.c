/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/28 19:55:52 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

static char	**get_commants(char **av, int count)
{
	char	**dst;
	int		i;

	i = 0;
	dst = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (0);
	while (i < count)
	{
		dst[i] = ft_strdup(av[i]);
		i++;
	}
	return (dst);
}

static void	pipex_data_init(t_pipex_data *data, int is_here_doc, int ac,
		char **av)
{
	if (is_here_doc)
	{
		data->here_doc_val = ft_strjoin(av[2], "\n");
		data->fd_in = -1;
		data->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND);
	}
	else
	{
		data->here_doc_val = NULL;
		data->fd_in = open(av[1], O_RDONLY);
		if (data->fd_in == -1)
		{
			perror("fail to open infile");
			exit(1);
		}
		data->fd_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR);
	}
	data->cmds = get_commants((av + 2), ac - 3);
	data->recur_depth = 0;
	pipe(data->p_fd1);
	pipe(data->p_fd2);
}

int	main(int ac, char const **av, char **envp)
{
	t_pipex_data	data;
	int				is_here_doc;

	if (ac < 5)
	{
		ft_printf("not enought args\n");
		return (1);
	}
	is_here_doc = !ft_strcmp(av[1], "here_doc");
	if (is_here_doc && ac < 6)
	{
		ft_printf("not enought args\n");
		return (1);
	}
	pipex_data_init(&data, is_here_doc, ac, (char **)av);
	if (is_here_doc)
		here_doc(&data, envp);
	else
		fork_recursion(&data, envp);
	return (0);
}
