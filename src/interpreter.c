/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/27 13:39:53 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "token.h"
#include "parser_error.h"

/*continue l'arbre en listes puis compounds, et recommence 
*jusqu'a ce qu'il n'y ait qu'une liste*/
static t_dlist	*ms_interpreter_loop(t_dlist *list)
{
	t_dlist	*list2;

	while (NULL != list->next)
	{
		list2 = ms_dlstnew(list, MS_PARSE_LIST);
		if (NULL == list2)
			return (ms_dlstclear(&list), NULL);
		if (0 != ms_list(list2))
			return (ms_dlstclear(&list2), NULL);
		if (NULL == list2->next)
			return (list2);
		list = ms_dlstnew(list2, MS_PARSE_CMP);
		if (NULL == list)
			return (ms_dlstclear(&list2), NULL);
		if (0 != ms_compound(list))
			return (ms_dlstclear(&list), NULL);
		if (NULL == list->next)
			return (list);
	}
	return (list);
}

/*cree l'arbre logique en token, puis commandes simples, puis pipelines*/
t_dlist	*ms_interpreter(char *input, void *data)
{
	t_dlist		*list;
	t_dlist		*list2;

	list = ms_token_list(input, data);
	if (NULL == list)
		return (NULL);
	if (0 == ms_parser_error(list, data) && 0 == ms_parse_here(list))
	{
		list2 = ms_dlstnew(list, MS_PARSE_CMD);
		if (NULL == list)
			return (NULL);
		if (0 != ms_cmd(list2))
			return (ms_dlstclear(&list2), NULL);
		list = ms_dlstnew(list2, MS_PARSE_PIPE);
		if (NULL == list)
			return (ms_dlstclear(&list), NULL);
		if (0 != ms_pipeline(list))
			return (ms_dlstclear(&list), NULL);
	}
	else
		return (ms_dlstclear(&list), NULL);
	return (ms_interpreter_loop(list));
}
