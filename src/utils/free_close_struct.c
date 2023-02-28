/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:15:33 by itan              #+#    #+#             */
/*   Updated: 2023/02/28 19:54:06 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_handle(int fd)
{
	if (close(fd))
	{
		perror("close");
		exit(1);
	}
}

void	free_2d(char **val)
{
	int	i;

	i = 0;
	while (val[i])
		free(val[i++]);
	free(val);
}

void	free_close_struct(t_pipex_data *data)
{
	free_2d(data->cmds);
	if (!data->here_doc_val)
		close_handle(data->fd_in);
	close_handle(data->fd_out);
	close_handle(data->p_fd1[0]);
	close_handle(data->p_fd2[1]);
	close_handle(data->p_fd1[1]);
	close_handle(data->p_fd2[0]);
}
