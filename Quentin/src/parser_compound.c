/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/24 12:39:21 by qgiraux          ###   ########.fr       */
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
		if (list->type == MS_TOKEN_OPEN && count == 0)
		{
			list = ms_dlst_free_link(list);
			count++;
			max_count++;
			if (list->prev != NULL)
			{
				ms_dlstcut(list);
				ms_dlstadd_back(&list, ms_dlstnew(cmp, MS_PARSE_CMP));
			}
			else
				cmp->type = MS_PARSE_CMP0;
		}
		if (list->type == MS_TOKEN_OPEN && count > 0)
		{
			count++;
			max_count++;
		}
		if (list->type == MS_TOKEN_CLOSE && count == 1)
		{
			list = ms_dlst_free_link(list);
			count--;
			if (list != NULL)
			{
				ms_dlstcut(list);
				ms_dlstadd_back(&list, ms_dlstnew(cmp, MS_PARSE_CMP0));
			}
		}
		if (list->type == MS_TOKEN_CLOSE && count > 1)
			count--;
		list = list->next;
	}
	return (0);
}
