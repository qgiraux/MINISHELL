/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:33:47 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/13 11:58:06 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*verifie si on est ala fin d'un pipeline*/
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

/*regroupe en un noeud PIPE les pipelines*/
int	ms_pipeline(t_dlist *pipes_list)
{
	t_dlist	*cmd;

	if (NULL == pipes_list)
		return (1);
	cmd = (t_dlist *)pipes_list->content;
	if (0 == ms_end(cmd))
		pipes_list->type = cmd->type;
	while (NULL != cmd)
	{
		if (1 == ms_end(cmd) && \
			(0 == ms_end(cmd->prev) || 0 == ms_end(cmd->next)))
			if (0 != ms_dlst_break_chain(pipes_list, cmd, cmd->type))
				return (1);
		if (2 == ms_end(cmd) && 0 == ms_end(cmd->prev))
			if (0 != ms_dlst_break_chain(pipes_list, cmd, MS_PARSE_PIPE))
				return (1);
		if (0 == ms_end(cmd) && NULL != cmd->prev)
			if (0 != ms_dlst_break_chain(pipes_list, cmd, cmd->type))
				return (1);
		cmd = cmd->next;
	}
	return (MS_SUCCESS);
}
