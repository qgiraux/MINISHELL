/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 14:16:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"


int	ms_compound(t_dlist *cmp)
{
	t_dlist	*list;
	int		count;
	int		max_count;

	count = 0;
	max_count = 0;
	list = (t_dlist *)cmp->content;
	while (list != NULL)
	{
		if (NULL != list->next && 1 == ms_dlist_istype_parenthesis(list->next) \
		&& 1 == ms_dlist_istype_pipe_and_or(list) && max_count == 0)
		{
			ms_dlstcut(list);
			ms_dlstadd_back(&cmp, ms_dlstnew(list, list->type));
		}
			
		if (MS_TOKEN_OPEN == list->type)
		{
			if (0 == count)
			{
				if (NULL == list->prev)
					cmp->type = MS_PARSE_CMP;
					
				if (NULL != list->prev)
				{
					ms_dlstcut(list);
					ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP));
				}
			}
			count++;
			max_count++;
		}
		if (MS_TOKEN_CLOSE == list->type)
		{
			list = list->next;
			count--;
			if (0 == count && NULL != list)
			{
				ms_dlstcut(list);
				if (1 == ms_dlist_istype_pipe_and_or(list))
					ms_dlstadd_back(&cmp, ms_dlstnew(list, list->type));
				if (0 == ms_dlist_istype_pipe_and_or(list))
					ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_LIST));
			}
		}
		else
			list = list->next;
	}
	return (max_count);
}
