/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 15:50:17 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

t_dlist	*ms_interpreter(char *input, const char **data)
{
	t_dlist		*token_head;
	t_dlist		*cmd_head;
	t_dlist		*pipe_head;
	t_dlist		*list_head;
	int			status;

	token_head = ms_token_list(input, data);
	status = parser_error(token_head, data);
	if (status == 0)
	{
		cmd_head = ms_dlstnew(token_head, MS_PARSE_CMD);
		status = ms_cmd(cmd_head);
		pipe_head = ms_dlstnew(cmd_head, MS_PARSE_PIPE0);
		status = ms_pipeline(pipe_head);
		list_head = ms_dlstnew(pipe_head, MS_PARSE_LIST);
		status = ms_list(list_head);
		status = -1;
		while (status < 0)
		{
			cmd_head = ms_dlstnew(list_head, MS_PARSE_CMP0);
			status = ms_compound(cmd_head);
			list_head = cmd_head;
		}
	}
	return (list_head);
}
