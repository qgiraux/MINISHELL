/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 14:34:57 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"

static int	check_next_parenth(t_dlist *list)
{
	t_dlist	*tmp;
	
	tmp = list->next;
	while (NULL != tmp)
	{
		if (MS_TOKEN_CLOSE == tmp->type)
			return (1);
		if (MS_TOKEN_OPEN == tmp->type)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

static t_dlist	*ms_is_it_cmp(t_dlist *list, t_dlist *cmp)
{
	if (1 == check_next_parenth(list))
	{
		if (NULL != list->prev)
			ms_dlst_break_chain(cmp, list, MS_PARSE_CMP);

		while (MS_TOKEN_CLOSE != list->type)
			list = list->next;
		list = list->next;
		if (NULL != list)
			ms_dlst_break_chain(cmp, list, list->type);			
	}
	else if (NULL != list->prev)
		ms_dlst_break_chain(cmp, list, list->type);
	return (list);
}

int	ms_compound(t_dlist *cmp)
{
	t_dlist	*list;
	int	status;

	status = 0;
	list = cmp->content;


	while (list)
	{
		if (MS_TOKEN_OPEN == list->type)
		{
			list = ms_is_it_cmp(list, cmp);
		}
		else if (NULL != list->prev)
			ms_dlst_break_chain(cmp, list, list->type);
		if (NULL != list)
			list = list->next;
	}
	return (status);	
}
