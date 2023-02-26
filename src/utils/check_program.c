/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:37:18 by itan              #+#    #+#             */
/*   Updated: 2023/02/26 15:14:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (*envp);
		envp++;
	}
	return (NULL);
}

void	free_2d(char **val)
{
	int	i;

	i = 0;
	while (val[i])
		free(val[i++]);
	free(val);
}

char	*check_program_exist(char *program_name, char **envp)
{
	char	**paths;
	char	*dst;
	int		i;

	i = 0;
	program_name = ft_strjoin("/", program_name);
	paths = ft_split(get_path(envp) + 5, ':');
	while (paths[i])
	{
		dst = ft_strjoin(paths[i++], program_name);
		if (!access(dst, F_OK))
		{
			free(program_name);
			free_2d(paths);
			return (dst);
		}
	}
	free(program_name);
	free_2d(paths);
	perror("program doesn't exist in path");
	return (NULL);
}
