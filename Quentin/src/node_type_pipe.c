/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:53:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 13:07:46 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_type.h"

static void	ms_free_p(t_pipe p, int nb_pipe)
{
	int	count;

	count = 0;
	while (count < nb_pipe)
	{
		free(p.pipefd[count]);
		count++;
	}
	free (p.pid);
	free (p.status);
	free (p.pipefd);
}
/*attribue les memoires necessaires pour les pid, pipes, et return values*/
t_pipe	ms_init_pipe(int nb_pipe)
{
	t_pipe	p;
	int		count;

	p.count = 0;
	p.pid = malloc(nb_pipe * sizeof(int));
	if (!p.pid)
		return (p);
	p.pipefd = malloc(nb_pipe * sizeof(int *));
	if (!p.pipefd)
		return (free(p.pid), p);
	p.status = malloc(nb_pipe * sizeof(int));
	if (!p.status)
		return (free(p.pid), free(p.pipefd), p);
	count = 0;
	while (count < nb_pipe)
	{
		p.pipefd[count] = malloc(2 * sizeof(int));
		if (!p.pipefd[count])
			return (ms_free_p(p, nb_pipe), p);
		count++;
	}
	return (p);
}
/*ce qui est execute dans chaque pipe*/
static int	ms_pipe_fork(t_pipe p, t_dlist *list, int nb_pipe, void *data)
{
	if (p.count > 0)
	{
		close (p.pipefd[p.count - 1][1]);
		dup2 (p.pipefd[p.count - 1][0], 0);
	}
	if (p.count < nb_pipe - 1)
	{
		close (p.pipefd[p.count][0]);
		dup2 (p.pipefd[p.count][1], 1);
	}
	exit (p.status[p.count] = ms_node_type(list, 0, data));
}
/*execute un fork et pipespour chaque pipe*/
static int	ms_pipe_loop(t_pipe p, int nb_pipe, t_dlist *list, void *data)
{
	p.count = 0;
	while (p.count < nb_pipe)
	{
		p.status[p.count] = 0;
		pipe(p.pipefd[p.count]);
		p.pid[p.count] = fork();
		if (-1 == p.pid[p.count])
			p.status[p.count] = 28;
		if (p.pid[p.count] == 0)
			p.status[p.count] = ms_pipe_fork(p, list, nb_pipe, data);
		list = list->next;
		while (list != NULL && list->type == MS_TOKEN_PIPE)
			list = list->next;
		close (p.pipefd[p.count][1]);
		p.count++;
	}
	p.count = 0;
	while (p.count < nb_pipe)
	{
		waitpid(p.pid[p.count], &p.status[p.count], 0);
		p.count++;
	}
	return (WEXITSTATUS(p.status[--p.count]));
}
/*si le noeud est un pipe, fait ce qu'il faut*/
int	ms_node_type_pipe(t_dlist *node, int status, void *data)
{
	t_dlist	*list;
	int		nb_pipe;
	t_pipe	p;

	list = node->content;
	if (NULL == list->next)
		return (ms_node_type(list, status, data));
	nb_pipe = 0;
	while (NULL != list)
	{
		if (MS_TOKEN_PIPE != list->type)
			nb_pipe++;
		list = list->next;
	}
	p = ms_init_pipe(nb_pipe);
	if (p.pipefd == NULL)
		return (1);
	status = ms_pipe_loop(p, nb_pipe, node->content, data);
	ms_free_p(p, nb_pipe);
	return (status);
}
