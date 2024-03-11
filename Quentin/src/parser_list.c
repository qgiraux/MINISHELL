/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:00:24 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 16:59:53 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*determine si on est a la fin d'une liste*/
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
/*determine si on doit decouper une liste, ou sielle est deja isolee*/
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
/*regroupe en un noeud LIST les listes*/
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
