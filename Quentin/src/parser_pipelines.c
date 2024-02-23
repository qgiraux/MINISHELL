/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:33:47 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 17:28:55 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_end_pipeline(t_dlist *cmd)
{
	int		op;
	t_dlist	*token;

	if (cmd == NULL)
		return (0);
	token = ((t_dlist *)(cmd->content));
	if (token == NULL)
		return (0);
	op = token->type;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

int	ms_pipeline(t_dlist *pipes_list)
{
	t_dlist	*cmd;

	if (NULL == pipes_list)
		return (1);
	cmd = (t_dlist *)pipes_list->content;
	cmd = cmd->next;
	while (cmd)
	{
		if (1 == ms_end_pipeline(cmd->prev))
		{
			ms_dlstcut(cmd);
			ms_dlstadd_back(&pipes_list, ms_dlstnew(cmd, cmd->type));
		}
		else if (1 == ms_end_pipeline(cmd))
		{
			ms_dlstcut(cmd);
			ms_dlstadd_back(&pipes_list, ms_dlstnew(cmd, MS_PARSE_PIPE));
		}
		cmd = cmd->next ;
	}
	return (0);
}
