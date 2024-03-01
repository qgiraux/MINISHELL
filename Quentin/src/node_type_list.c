/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:09:41 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 13:26:35 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"
#include "../includes/token.h"


int	node_type_list(t_dlist *node, int status, const char **data)
{
	t_dlist	*list;

	list = node->content;

	while (NULL != list)
	{
		if (1 == ms_dlist_istype_pipe_and_or(list))
		{
			if (MS_TOKEN_AND == list->type)
			{
				list = list->next;
				if (status != 0)
					list = list->next;	
			}
			if (MS_TOKEN_OR == list->type)
			{
				list = list->next;
				if (status == 0)
					list = list->next;	
			}
		}
		else
		{
			status = node_type(list, status, data);
			list = list->next;
		}
	}
	return (status);
	
}