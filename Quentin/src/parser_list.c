/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:00:24 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/29 11:06:02 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*liste est une serie de PIPES separes de ET ou OU*/
/* les ET et OU qui ne separent pas 2 PIPES ne font pas partie de LISTE*/
static int	ms_end(t_dlist *cmd)
{
	int		op;

	if (cmd == NULL)
		return (-1);
	op = cmd->type;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR)
		return (1);
	if (op == MS_PARSE_PIPE || op == MS_PARSE_CMP || op == MS_PARSE_LIST)
		return (2);
	return (0);
}

static int	check_if_cut(t_dlist *cmd, t_dlist *list, int check)
{
	if (0 == ms_end(cmd) && NULL != cmd->prev)
		ms_dlst_break_chain(list, cmd, cmd->type);
	if (1 == ms_end(cmd))
	{
		if (2 != ms_end(cmd->prev) || 2 != ms_end(cmd->next))
		{
			check = 1;
			ms_dlst_break_chain(list, cmd, cmd->type);
		}
	}
	if (2 == ms_end(cmd))
	{
		if (1 == check || 0 == ms_end(cmd->prev))
		{
			ms_dlst_break_chain(list, cmd, MS_PARSE_LIST);
			check = 0;
		}
	}
	return (check);
}

int	ms_list(t_dlist *list)
{
	t_dlist	*cmd;
	int		check;

	if (NULL == list)
		return (1);
	cmd = (t_dlist *)list->content;
	if (0 == ms_end(cmd))
		list->type = cmd->type;
	while (NULL != cmd)
	{
		check = check_if_cut(cmd, list, check);
		cmd = cmd->next;
	}
	return (0);
}
