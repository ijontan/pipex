/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:19:13 by itan              #+#    #+#             */
/*   Updated: 2023/02/26 20:31:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	print_struct(t_pipex_data *data)
// {
// 	// print2d(data->cmds);
// 	ft_printf("pipe in:%i\n", data->p_fd1[0]);
// 	ft_printf("pipe out:%i\n", data->p_fd1[1]);
// 	ft_printf("%i\n", data->recur_depth);
// }

// void	print_input(int fd)
// {
// 	char	reading_buff;

// 	ft_printf("%i", fd);
// 	while (read(fd, &reading_buff, 1) > 0)
// 	{
// 		write(1, &reading_buff, 1); // 1 -> stdout
// 	}
// }

static void	child_process(t_pipex_data *data, char **envp)
{
	char	**final_argv;
	char	*final_program_name;
	int		status;

	waitpid(-1, &status, 0);
	ft_printf("\nchild:\n");
	// print_struct(data);
	data->recur_depth++;
	final_argv = ft_split(data->cmds[data->recur_depth], ' ');
	final_program_name = check_program_exist(final_argv[0], envp);
	// ft_printf("%s\n", final_program_name);
	// print2d(final_argv);
	if (data->cmds[data->recur_depth + 1])
		return (fork_recursion(data, envp));
	// print_input(data->p_fd1[0]);
	if (data->recur_depth % 2 == 1)
		dup2(data->p_fd1[0], STDIN_FILENO);
	else
		dup2(data->p_fd2[0], STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	free_close_struct(data);
	execve(final_program_name, final_argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	parent_process(t_pipex_data *data, char **envp)
{
	char	**final_argv;
	char	*final_program_name;

	// ft_printf("parent:\n");
	// print_struct(data);
	final_argv = ft_split(data->cmds[data->recur_depth], ' ');
	final_program_name = check_program_exist(final_argv[0], envp);
	// ft_printf("%s\n", final_program_name);
	// print2d(final_argv);
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
	free_close_struct(data);
	execve(final_program_name, final_argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fork_recursion(t_pipex_data *data, char **envp)
{
	pid_t	pid;

	// int		status;
	// if (data->p_fd2[0] != -1)
	// 	close(data->p_fd2[0]);
	// if (data->p_fd2[1] != -1)
	// 	close(data->p_fd2[1]);
	// data->p_fd2[0] = data->p_fd1[0];
	// data->p_fd2[1] = data->p_fd1[1];
	// pipe(data->p_fd1);
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
		child_process(data, envp);
	else
		parent_process(data, envp);
	// waitpid(pid, &status, 0);
}
