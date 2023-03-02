/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:37:18 by itan              #+#    #+#             */
/*   Updated: 2023/03/02 17:01:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp, t_pipex_data *data)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (*envp);
		envp++;
	}
	free_close_struct(data);
	perror("PATH not found");
	exit(127);
	return (NULL);
}

char	*check_program_exist(char *program_name, char **envp,
		t_pipex_data *data)
{
	char	**paths;
	char	*dst;
	int		i;

	i = 0;
	dst = NULL;
	program_name = ft_strjoin("/", program_name);
	paths = ft_split(get_path(envp, data) + 5, ':');
	while (paths[i])
	{
		dst = ft_strjoin(paths[i++], program_name);
		if (!access(dst, F_OK))
		{
			free(program_name);
			free_2d(paths);
			return (dst);
		}
		if (dst)
			free(dst);
	}
	free(program_name);
	free_2d(paths);
	perror("program doesn't exist in path");
	return (NULL);
}
