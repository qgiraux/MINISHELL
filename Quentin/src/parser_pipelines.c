/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:33:47 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 13:17:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_end(t_dlist *cmd)
{
	int		op;

	if (cmd == NULL)
		return (-1);
	op = cmd->type;
	if (op == MS_TOKEN_PIPE)
		return (1);
	if (op == MS_PARSE_CMD)
		return (2);
	return (0);
}
/* au lieu de delimiter les pipes par AND OR OPEN CLOSE, les regouper par commandes simples separees de pipes*/
/* degager le type CMD, ne faire que des PIPES a ce niveau*/

int	ms_pipeline(t_dlist *pipes_list)
{
	t_dlist	*cmd;

	if (NULL == pipes_list)
		return (1);
	cmd = (t_dlist *)pipes_list->content;

	while (NULL != cmd)
	{
		if (1 == ms_end(cmd))
			if (0 == ms_end(cmd->prev) || 0 == ms_end(cmd->next))
				ms_dlst_break_chain(pipes_list, cmd, cmd->type);
		if (2 == ms_end(cmd))
			if (0 == ms_end(cmd->prev))
				ms_dlst_break_chain(pipes_list, cmd, MS_PARSE_PIPE);
		if (0 == ms_end(cmd))
			ms_dlst_break_chain(pipes_list, cmd, cmd->type);
		cmd = cmd->next;
	}
	return (0);
}

