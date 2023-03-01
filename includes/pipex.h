/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:32:55 by itan              #+#    #+#             */
/*   Updated: 2023/03/01 16:22:50 by itan             ###   ########.fr       */
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
	char	*here_doc_val;
	char	**cmds;
	int		fd_in;
	int		fd_out;
	int		recur_depth;
}			t_pipex_data;

char		*check_program_exist(char *program_name, char **envp);
void		fork_recursion(t_pipex_data *data, char **envp);
void		free_2d(char **val);
void		free_close_struct(t_pipex_data *data);
void		here_doc(t_pipex_data *data, char **envp);
#endif