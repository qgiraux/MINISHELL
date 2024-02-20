/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:33:47 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/20 19:21:41 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	op = ((t_token *)(token->content))->operator;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

t_dlist	*ms_pipeline_list(t_dlist *cmd)
{
	t_dlist	*pipes_list;

	if (NULL == cmd)
		return (NULL);
	pipes_list = NULL;
	pipes_list = ms_dlstnew(cmd);
	cmd = cmd->next;
	while (cmd)
	{
		if (1 == ms_end_pipeline(cmd) || 1 == ms_end_pipeline(cmd->prev))
		{
			ms_dlstcut(cmd);
			ms_dlstadd_back(&pipes_list, ms_dlstnew(cmd));
		}
		cmd = cmd->next ;
	}
	return (pipes_list);
}
