/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:32:55 by itan              #+#    #+#             */
/*   Updated: 2023/02/26 18:18:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex_data
{
	int		p_fd1[2];
	int		p_fd2[2];
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		recur_depth;
}			t_pipex_data;

char		*check_program_exist(char *program_name, char **envp);
char		**lst_join(char **a, char **b);
void		fork_recursion(t_pipex_data *data, char **envp);
void		print2d(char **val);
void		free_2d(char **val);
void		free_close_struct(t_pipex_data *data);
#endif