/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:09:41 by qgiraux           #+#    #+#             */
/*   Updated: 2024/04/01 15:26:28 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

/*determine si on execute la commande suivante, selon && ou ||*/
static t_dlist	*ms_list_and_or(t_dlist *list, int status)
{
	if (NULL == list)
		return (list);
	if (MS_TOKEN_AND == list->type)
	{
		if (status != 0)
			list = list->next;
	}
	else if (MS_TOKEN_OR == list->type)
	{
		if (status == 0)
			list = list->next;
	}
	return (list);
}

/*si le noeud est une liste, fait ce qu'il faut*/
int	ms_node_list(t_dlist *node, int status, void *data, int compare)
{
	t_dlist	*list;

	list = node->content;
	if (MS_PARSE_LIST == list->type)
	{
		status = ms_node(list, status, data, compare);
		list = list->next;
	}
	else if ((compare == MS_TOKEN_AND && status != 0) \
	|| (compare == MS_TOKEN_OR && status == 0))
		list = list->next;
	compare = 0;
	while (NULL != list)
	{
		if (1 == ms_dlist_istype_pipe_list(list))
		{
			compare = list->type;
			if (MS_PARSE_LIST != list->next->type)
				list = ms_list_and_or(list, status);
		}
		else
			status = ms_node(list, status, data, compare);
		list = list->next;
	}
	return (status);
}
