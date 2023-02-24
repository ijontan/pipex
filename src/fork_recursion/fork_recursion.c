/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_recursion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:19:13 by itan              #+#    #+#             */
/*   Updated: 2023/02/23 18:30:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_recursion(char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	else if (pid == 0)
		child_process();
	else
		parent_process();
}
