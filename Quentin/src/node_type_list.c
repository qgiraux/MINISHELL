/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:09:41 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 13:05:55 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_type.h"

/*determine si on execute la commande suivante, selon && ou ||*/
static t_dlist	*ms_list_and_or(t_dlist *list, int status)
{
	if (NULL == list)//
		return (list);//
	if (MS_TOKEN_AND == list->type)
	{
		list = list->next;
		if (status != 0)
			list = list->next;
	}
	else if (MS_TOKEN_OR == list->type)
	{
		list = list->next;
		if (status == 0)
			list = list->next;
	}
	return (list);
}
/*si le noeud est une liste, fait ce qu'il faut*/
int	ms_node_type_list(t_dlist *node, int status, void *data)
{
	t_dlist	*list;

	if (NULL == node)//
		return (status);//
	list = node->content;
	
	while (NULL != list)
	{
		if (1 == ms_dlist_istype_pipe_and_or(list))
			list = ms_list_and_or(list, status);
		else
		{
			status = ms_node_type(list, status, data);
			list = list->next;
		}
	}
	return (status);
}
