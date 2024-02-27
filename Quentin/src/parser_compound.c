/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 16:30:29 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"

int	check_open_parenth(t_dlist *list)
{
	t_dlist	*tmp;

	tmp = list->next;
	while (tmp)
	{
		if (MS_TOKEN_OPEN == tmp->type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ms_compound(t_dlist *cmp)
{
	t_dlist	*list;
	int		check;

	check = 0;
	list = (t_dlist *)cmp->content;
	while (list)
	{
		if (MS_TOKEN_OPEN == list->type && 0 == check_open_parenth(list))
		{
			ms_dlst_break_chain(cmp, list, MS_PARSE_CMP);
			while (MS_TOKEN_CLOSE != list->type)
				list = list->next;
			list = list->next;
			if (list)
				ms_dlst_break_chain(cmp, list, MS_PARSE_LIST);
		}
		if (MS_TOKEN_OPEN == list->type && 1 == check_open_parenth(list))
			check = -1;
		list = list->next;
	}
	return (check);
}
