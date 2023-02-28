/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:53:52 by itan              #+#    #+#             */
/*   Updated: 2023/02/28 17:24:51 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_process(t_pipex_data *data, char **envp, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	data->recur_depth++;
	fork_recursion(data, envp);
}

static void	child_process(t_pipex_data *data)
{
	char	*dst;
	int		not_same;
	char	*tmp;

	dst = NULL;
	write(1, "> ", 2);
	tmp = get_next_line(STDIN_FILENO);
	not_same = ft_strcmp(tmp, data->here_doc_val);
	dst = ft_append(dst, tmp);
	free(tmp);
	while (not_same != 0)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		not_same = ft_strcmp(tmp, data->here_doc_val);
		if (not_same)
			dst = ft_append(dst, tmp);
		free(tmp);
	}
	write(data->p_fd1[1], dst, ft_strlen(dst));
	free(dst);
	exit(0);
}

void	here_doc(t_pipex_data *data, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		child_process(data);
	else
		parent_process(data, envp, pid);
}
