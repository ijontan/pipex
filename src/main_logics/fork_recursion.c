/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:19:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/02 17:02:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_fd_child(t_pipex_data *data)
{
	if (data->recur_depth % 2 == 1)
		dup2(data->p_fd1[0], STDIN_FILENO);
	else
		dup2(data->p_fd2[0], STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
}

static void	child_process(t_pipex_data *data, char **envp, int pid)
{
	char	**final_argv;
	char	*final_program_name;
	int		status;

	waitpid(pid, &status, 0);
	data->recur_depth++;
	if (data->cmds[data->recur_depth + 1])
		return (fork_recursion(data, envp));
	set_fd_child(data);
	final_argv = ft_split(data->cmds[data->recur_depth], ' ');
	final_program_name = check_program_exist(final_argv[0], envp, data);
	free_close_struct(data);
	if (!final_program_name)
		exit(1);
	execve(final_program_name, final_argv, envp);
	free_2d(final_argv);
	free(final_program_name);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	set_fd_parent(t_pipex_data *data)
{
	if (data->recur_depth == 0)
		dup2(data->fd_in, STDIN_FILENO);
	else
	{
		if (data->recur_depth % 2 == 1)
			dup2(data->p_fd1[0], STDIN_FILENO);
		else
			dup2(data->p_fd2[0], STDIN_FILENO);
	}
	if (data->recur_depth % 2 == 0)
		dup2(data->p_fd1[1], STDOUT_FILENO);
	else
		dup2(data->p_fd2[1], STDOUT_FILENO);
}

static void	parent_process(t_pipex_data *data, char **envp)
{
	char	**final_argv;
	char	*final_program_name;

	set_fd_parent(data);
	final_argv = ft_split(data->cmds[data->recur_depth], ' ');
	final_program_name = check_program_exist(final_argv[0], envp, data);
	free_close_struct(data);
	if (!final_program_name)
		exit(1);
	execve(final_program_name, final_argv, envp);
	free_2d(final_argv);
	free(final_program_name);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fork_recursion(t_pipex_data *data, char **envp)
{
	pid_t	pid;

	if (data->recur_depth % 2 == 0)
	{
		close(data->p_fd1[0]);
		close(data->p_fd1[1]);
		pipe(data->p_fd1);
	}
	else
	{
		close(data->p_fd2[0]);
		close(data->p_fd2[1]);
		pipe(data->p_fd2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		child_process(data, envp, pid);
	else
		parent_process(data, envp);
}
