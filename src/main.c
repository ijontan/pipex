/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:06 by itan              #+#    #+#             */
/*   Updated: 2023/02/23 00:18:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char const **av)
{
	char	**argv;
	char	**env;

	argv = (char **){NULL};
	env = (char **){NULL};
	(void)(ac);
	(void)(av);
	if (access("/usr/bin/make", F_OK))
		perror("access fail");
	if (execve("/usr/bin/make", argv, env))
		perror("execve fail");
	return (0);
}
