/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 14:31:33 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/parser_error.h"
#include "../includes/node_type.h"

static t_dlist	*ms_interpreter_loop(t_dlist *list, int status)
{
	while (NULL != list->next || 0 != status)
	{
		list = ms_dlstnew(list, MS_PARSE_LIST);
		if (NULL == list)
			return (NULL);
		status += ms_list(list);
		if (0 != status)
			return (free_input(list), NULL);
		if (NULL == list->next || 0 != status)
			return (list);
		list = ms_dlstnew(list, MS_PARSE_CMP);
		if (NULL == list)
			return (NULL);
		status += ms_compound(list);
		if (0 != status)
			return (free_input(list), NULL);
	}
	return (list);
}

t_dlist	*ms_interpreter(char *input, const char **data)
{
	t_dlist		*list;
	int			status;

	status = 0;
	list = ms_token_list(input, data);
	if (0 == ms_parser_error(list, data))
	{
		list = ms_dlstnew(list, MS_PARSE_CMD);
		if (NULL == list)
			return (NULL);
		status = ms_cmd(list);
		if (0 != status)
			return (free_input(list), NULL);
		list = ms_dlstnew(list, MS_PARSE_PIPE);
		if (NULL == list)
			return (NULL);
		status = ms_pipeline(list);
		if (0 != status)
			return (free_input(list), NULL);
	}
	else
		return (free_input(list), NULL);
	return (ms_interpreter_loop(list, status));
}
