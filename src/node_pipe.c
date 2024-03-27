/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:53:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/27 13:03:12 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "error.h"
#include "data.h"
#include "node_pipe_utils.h"
#include "sig.h"

static void	ms_child(t_dlist *list, void *data, int *pipefd, int fd_in)
{
	int		exit_code;

	ms_sig_ignore(SIGINT, 1);
	dup2(fd_in, 0);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (fd_in != 0)
		close(fd_in);
	close(pipefd[0]);
	exit_code = ms_node(list, 0, data);
	ms_exit_pipe(NULL, data, exit_code);
}

static pid_t	ms_last_loop(t_dlist *list, void *data, int *pipefd, pid_t *p0)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (-1 == pid)
		ms_exit_pipe("Fork", data, 1);
	else if (pid == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		free (p0);
		exit_code = ms_node(list, 0, data);
		ms_exit_pipe(NULL, data, exit_code);
	}
	else
		close(pipefd[1]);
	return (pid);
}

static int	ms_not_child(t_dlist *list, int fd_in, int *pipefd)
{
	if (NULL != list->prev)
		close(fd_in);
	close(pipefd[1]);
	fd_in = pipefd[0];
	return (fd_in);
}

int	ms_run_pipeline(t_dlist *list, void *data, pid_t *pid, int i)
{
	int		pipefd[2];
	int		fd_in;

	fd_in = 0;
	while (NULL != list->next)
	{
		if (-1 == pipe(pipefd))
			ms_exit_pipe("Pipe", data, 1);
		pid[i] = fork();
		if (-1 == pid[i])
			ms_exit_pipe("Fork", data, 1);
		else if (pid[i] == 0)
		{
			free(pid);
			ms_child(list, data, pipefd, fd_in);
		}
		else
			fd_in = ms_not_child(list, fd_in, pipefd);
		list = list->next->next;
		i++;
	}
	pipefd[1] = fd_in;
	pid[i] = ms_last_loop(list, data, pipefd, pid);
	fd_in = ms_loop_close_init(ms_dlstfirst(list), pid, data, 0);
	return (free(pid), fd_in);
}

int	ms_node_pipe(t_dlist *node, int status, void *data)
{
	t_dlist	*list;
	int		nb_pid;
	pid_t	*pid;

	ms_sig_ignore(SIGINT, 1);
	ms_sig_ignore(SIGQUIT, 1);
	(void)status;
	nb_pid = 0;
	list = node->content;
	while (NULL != list->next)
	{
		nb_pid++;
		list = list->next->next;
	}
	pid = malloc((nb_pid + 1) * sizeof(pid_t));
	list = node->content;
	if (NULL == list->next)
		return (free(pid), ms_node(list, 0, data));
	return (ms_run_pipeline(node->content, data, pid, 0));
}
