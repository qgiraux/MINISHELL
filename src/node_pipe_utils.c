/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:12:16 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/28 11:27:22 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "error.h"
#include "data.h"
#include "sig.h"

int	ms_pipe_loop_close(pid_t pid, void *data, int status)
{
	pid_t	rpid;

	rpid = waitpid(pid, &status, 0);
	if (-1 == rpid)
		return (ms_perror(MS_E), 1);
	else if (0 == rpid)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		ms_data_exit_pipe_set(status, data);
		if (status > MS_EXIT_FATAL_SIG)
		{
			g_signum = status - MS_EXIT_FATAL_SIG;
			errno = EINTR;
		}
		return (status);
	}
	else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		return (status);
	}
	return (ms_e(__FILE__, __LINE__, 1), 1);
}

void	ms_exit_pipe(char *error, void *data, int exit_code)
{
	if (NULL != error)
		ms_perror(error);
	ms_data_destroy_main(data);
	exit (exit_code);
}

int	ms_loop_close_init(t_dlist *list, pid_t *pid, void *data, int i)
{
	int	status;

	while (NULL != list)
	{
		status = ms_pipe_loop_close(pid[i++], data, status);
		list = list->next;
		if (NULL != list)
			list = list->next;
	}
	return (status);
}
