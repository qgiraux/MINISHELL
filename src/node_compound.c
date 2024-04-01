/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:21:52 by qgiraux           #+#    #+#             */
/*   Updated: 2024/04/01 13:38:11 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

/*si le noeud est un compound, fait ce qu'il faut*/
int	ms_node_compound(t_dlist *node, int status, void *data)
{
	t_dlist	*list;

	list = node->content;
	while (NULL != list)
	{
		if (MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type)
			list = list->next;
		return (ms_node(list, status, data, 0));
	}
	return (status);
}
