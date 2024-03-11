/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 15:27:08 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh_utils.h"
#include "../includes/node_type.h"
#include "../includes/token.h"
#include "../includes/parser_error.h"
#include "../includes/minishell.h"

/*continue l'arbre en listes puis compounds, et recommence 
*jusqu'a ce qu'il n'y ait qu'une liste*/
static t_dlist	*ms_interpreter_loop(t_dlist *list, int status)
{
	while (NULL != list->next || 0 != status)
	{
		list = ms_dlstnew(list, MS_PARSE_LIST);
		if (NULL == list)
			return (NULL);
		status += ms_list(list);
		if (0 != status)
			return (ms_free_input(list), NULL);
		if (NULL == list->next || 0 != status)
			return (list);
		list = ms_dlstnew(list, MS_PARSE_CMP);
		if (NULL == list)
			return (NULL);
		status += ms_compound(list);
		if (0 != status)
			return (ms_free_input(list), NULL);
	}
	return (list);
}

/*cree l'arbre logique en token, puis commandes simples, puis pipelines*/
t_dlist	*ms_interpreter(char *input, void *data)
{
	t_dlist		*list;
	int			status;

	status = 0;
	list = ms_token_list(input, data);
	if (0 == ms_parser_error(list, data) && 0 == ms_parse_here(list))
	{
		list = ms_dlstnew(list, MS_PARSE_CMD);
		if (NULL == list)
			return (NULL);
		status = ms_cmd(list);
		if (0 != status)
			return (ms_free_input(list), NULL);
		list = ms_dlstnew(list, MS_PARSE_PIPE);
		if (NULL == list)
			return (NULL);
		status = ms_pipeline(list);
		if (0 != status)
			return (ms_free_input(list), NULL);
	}
	else
		return (ms_free_input(list), NULL);
	return (ms_interpreter_loop(list, status));
}
