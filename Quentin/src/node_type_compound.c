/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_compound.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:21:52 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 13:29:47 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"


int	node_type_compound(t_dlist *node, int status, const char **data)
{	
	t_dlist *list;

	list = node->content;
	while (NULL != list)
	{
		if (MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type)
			list = list->next;
		return (node_type(list, status, data));
	}
	return (status);	
}