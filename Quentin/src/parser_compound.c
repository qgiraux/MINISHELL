/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 18:32:26 by qgiraux          ###   ########.fr       */
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
	if (NULL == cmp)
		return (1);
	list = (t_dlist *)cmp->content;
	while (list)
	{
		if (list->type == MS_TOKEN_OPEN)
		{
			if (count == 0)
			{
				
				ms_dlstcut(list);
				list = ms_dlst_free_link(list);
				ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP));

			}
			count++;
			max_count++;
		}
		else if (list->type == MS_TOKEN_CLOSE)
		{
			if (count == 1)
			{
				ms_dlstcut(list->next);
				list = ms_dlst_free_link(list);
				ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP0));
			}
			if (count == 0)
				return (printf ("error parenthesis"), 1);
			count--;
		}
		list = list->next;
	}
	if (max_count > 1)
		return (ms_compound(ms_dlstnew(cmp, MS_PARSE_CMP0)));
	return (0);
}