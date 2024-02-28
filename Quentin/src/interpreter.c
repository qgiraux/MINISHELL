/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 15:41:40 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

t_dlist	*ms_interpreter(char *input, const char **data)
{
	t_dlist		*list;
	int			status;

	status = 0;
	list = ms_token_list(input, data);
	if (0 == parser_error(list, data))
	{
		list = ms_dlstnew(list, MS_PARSE_CMD);
		status += ms_cmd(list);
		list = ms_dlstnew(list, MS_PARSE_PIPE);
		status += ms_pipeline(list);
		while (NULL != list->next || 0 != status)
		{
			list = ms_dlstnew(list, MS_PARSE_LIST);
			status += ms_list(list);
			if (NULL == list->next || 0 != status)
				return (list);
			list = ms_dlstnew(list, MS_PARSE_CMP);
			status += ms_compound(list);
		}
	}
	return (list);
}
