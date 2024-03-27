/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/13 17:59:03 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*determine si il y a une autre parenthese imbriquee*/
static int	ms_check_next_parenth(t_dlist *list)
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

/*decoupele bloc d'un compond, et l'ajoute a la liste chainee*/
static t_dlist	*ms_is_it_cmp(t_dlist *list, t_dlist *cmp)
{
	if (1 == ms_check_next_parenth(list))
	{
		if (NULL != list->prev)
			if (0 != ms_dlst_break_chain(cmp, list, MS_PARSE_CMP))
				return (NULL);
		while (MS_TOKEN_CLOSE != list->type)
			list = list->next;
		list = list->next;
		if (NULL != list)
			if (0 != ms_dlst_break_chain(cmp, list, list->type))
				return (NULL);
	}
	else if (NULL != list->prev)
		if (0 != ms_dlst_break_chain(cmp, list, list->type))
			return (NULL);
	return (list);
}

/*regroupe en un noeud CMP les compounds*/
int	ms_compound(t_dlist *cmp)
{
	t_dlist	*list;

	list = cmp->content;
	if (MS_PARSE_LIST == list->type || 1 != ms_check_next_parenth(list))
		cmp->type = list->type;
	while (list)
	{
		if (MS_TOKEN_OPEN == list->type)
		{
			list = ms_is_it_cmp(list, cmp);
		}
		else if (NULL != list->prev)
			if (0 != ms_dlst_break_chain(cmp, list, list->type))
				return (1);
		if (NULL != list)
			list = list->next;
	}
	return (MS_SUCCESS);
}
