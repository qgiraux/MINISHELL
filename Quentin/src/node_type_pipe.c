/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:53:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/02 13:45:42 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"
#include "../includes/token.h"


t_pipe	init_pipe(int nb_pipe)
{
	t_pipe	p;
	int		count;

	p.count = 0;
	p.pid = malloc(nb_pipe * sizeof(int));
	if (!p.pid)
		return (p);
	p.pipefd = malloc(nb_pipe * sizeof(int *));
	if (!p.pipefd)
	{
		free(p.pid);
		return (p);
	}
	p.status = malloc(nb_pipe * sizeof(int));
	if (!p.status)
	{
		free(p.pid);
		free(p.pipefd);
		return (p);
	}
	count = 0;
	while (count < nb_pipe)
	{
		p.pipefd[count] = malloc(2 * sizeof(int));
		if (!p.pipefd[count])
			{
				while (count >=0)
					free(p.pipefd[count--]);
				free(p.pid);
				free(p.pipefd);
				free(p.status);
				return (p);
			}
		count++;
	}
	return (p);	
}

void	free_p(t_pipe p, int nb_pipe)
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

int	pipe_fork(t_pipe p, t_dlist *list, int nb_pipe, const char **data)
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
	exit (p.status[p.count] = node_type(list, 0, data));
}

int	pipe_loop(t_pipe p, int nb_pipe, t_dlist *list, const char **data)
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
			p.status[p.count] = pipe_fork(p, list, nb_pipe, data);
		list = list->next;
		while (list != NULL && list->type == MS_TOKEN_PIPE)
			list = list->next;
		close (p.pipefd[p.count][0]);
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


int	node_type_pipe(t_dlist *node, int status, const char **data)
{
	t_dlist	*list;
	int		nb_pipe;
	t_pipe	p;
	
	list = node->content;
	if (NULL == list->next)
		return(node_type(list, status, data));
	nb_pipe = 0;
	while (NULL != list)
	{
		if (MS_TOKEN_PIPE != list->type)
			nb_pipe++;
		list = list->next;		
	}
	p = init_pipe(nb_pipe);
	if (p.pipefd == NULL)
		return (1);
	status = pipe_loop(p, nb_pipe, node->content, data);
	free_p(p, nb_pipe);
	return (status);
}
