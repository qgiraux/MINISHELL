/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:33:47 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 12:45:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_end(t_dlist *cmd)
{
	int		op;
	t_dlist	*token;

	if (cmd == NULL)
		return (0);
	token = ((t_dlist *)(cmd->content));
	if (token == NULL)
		return (0);
	op = token->type;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR \
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

static void	pipe_type(t_dlist *pipes_list, int type)
{
	t_dlist	*tmp;

	tmp = pipes_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->type = type;
}

int	ms_pipeline(t_dlist *pipes_list)
{
	t_dlist	*cmd;

	if (NULL == pipes_list)
		return (1);
	cmd = (t_dlist *)pipes_list->content;
	while (NULL != cmd)
	{
		if (MS_TOKEN_PIPE == cmd->type)
			pipe_type(pipes_list, MS_PARSE_PIPE);
		else if (1 == ms_end(cmd))
		{
			if (NULL != cmd->prev)
			{
				ms_dlstcut(cmd);
				ms_dlstadd_back(&pipes_list, ms_dlstnew(cmd, cmd->type));
			}
			else
				pipe_type(pipes_list, cmd->type);
		}
		else if (1 == ms_end(cmd->prev))
		{
			ms_dlstcut(cmd);
			ms_dlstadd_back(&pipes_list, ms_dlstnew(cmd, MS_PARSE_CMD));
		}
		cmd = cmd->next;
	}
	return (0);
}
