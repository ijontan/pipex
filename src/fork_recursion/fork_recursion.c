/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:19:13 by itan              #+#    #+#             */
/*   Updated: 2023/02/25 04:00:53 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **args, pid_t pid, int *status)
{
	waitpid(pid, status, WUNTRACED);
	(void)args;
}

void	parent_process(char **args, pid_t pid, int *status)
{
	waitpid(pid, status, WUNTRACED);
	(void)args;
}

void	fork_recursion(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	else if (pid == 0)
		child_process(args, pid, &status);
	else
		parent_process(args, pid, &status);
}
