/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 14:10:04 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"

int	ms_end_compound(t_dlist *cmd)
{
	int		op;
	t_dlist	*token;

	if (cmd == NULL)
		return (0);
	token = ((t_dlist *)(cmd->content));
	if (token == NULL)
		return (0);
	op = token->type;
	if (op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE || op == MS_TOKEN_PIPE)
		return (1);
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR)
		return (2);
	return (0);
}

int	ms_compound(t_dlist *cmp)
{
	t_dlist	*list;
	int		count;

	count = 0;
	if (NULL == cmp)
		return (1);
	list = (t_dlist *)cmp->content;
	while (list)
	{
		if (list->type == MS_TOKEN_OPEN)
		{
			if (count == 0)
			{
				ms_dlstcut(list);
				ms_dlstadd_back(&list, ms_dlstnew(list, MS_PARSE_CMP));

			}
			count++;
		}
		if (list->type == MS_TOKEN_CLOSE)
		{
			if (count == 1)
			{
				ms_dlstcut(list->next);
				ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP));
			}
			if (count == 0)
				return (printf ("error parenthesis"), 1);
		}
		list = list->next;
	}
	return (0);
}