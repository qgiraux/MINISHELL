/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:53:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 17:44:55 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"
#include "../includes/token.h"


t_pipe	init_pipe(int i)
{
	t_pipe	p;
	int		count;

	count = 0;
	p.i = 0;
	p.pid = malloc(i * sizeof(int));
	if (!p.pid)
		return (p);
	p.pipefd = malloc(i * sizeof(int *));
	if (!p.pipefd)
	{
		free(p.pid);
		return (p);
	}
	p.status = malloc(i * sizeof(int));
	if (!p.status)
	{
		free(p.pid);
		free(p.pipefd);
		return (p);
	}
	while (count < i)
	{
		p.pipefd[count] = malloc(2 * sizeof(int));
		count++;
	}
	return (p);	
}

int	pipe_fork(t_pipe p, int i, t_dlist *list, const char **data)
{
	if (p.i > 0)
	{
		close (p.pipefd[p.i - 1][1]);
		dup2 (p.pipefd[p.i - 1][0], 0);
	}
	if (p.i < i)
	{
		close (p.pipefd[p.i][0]);
		dup2 (p.pipefd[p.i][1], 1);
	}
	return (node_type(list, p.status[p.i], data));
}

int	pipe_loop(t_pipe p, int i, t_dlist *list, const char **data)
{
	while (p.i < i)
	{
		p.status[p.i] = 0;
		pipe(p.pipefd[p.i]);
		p.pid[i] = fork();
		if (-1 == p.pid[p.i])
			p.status[p.i] = 28;
		if (p.pid[p.i] == 0)
			p.status[p.i] = pipe_fork(p, i, list, data);
		while (list->next == MS_TOKEN_PIPE)
			list = list->next;
		p.i++;
		close (p.pipefd[p.i][1]);
	}
	while (--p.i >= 0)
		waitpid(p.pid[p.i], &p.status[i], 0);
	return (WEXITSTATUS(p.status[i]));
}


int	node_type_pipe(t_dlist *node, int status, const char **data)
{
	t_dlist	*list;
	int		i;
	t_pipe	p;
	
	list = node->content;
	if (NULL == list->next)
		return(node_type(list, status, data));
	i = 0;
	while (NULL != list)
	{
		if (MS_TOKEN_PIPE != list->type)
			i++;
		list = list->next;		
	}
	list = node->content;
	p = init_pipe(i);
	if (!p.pid)
		return (1);
	status = pipe_loop(p, i, list, data);
	return (status);
}