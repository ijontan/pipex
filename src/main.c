/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/23 18:15:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	split_process(void)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	else if (pid == 0)
// 		printf();
// 	else
// 		printf();
// }

int	main(int ac, char const **av, char **envp)
{
	char	*dst;

	(void)ac;
	dst = check_program_exist((char *)av[1], envp);
	if (dst)
		ft_printf(dst);
	return (0);
}
