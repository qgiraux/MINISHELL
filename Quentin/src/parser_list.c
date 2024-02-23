/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:00:24 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 17:32:57 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_end_list(t_dlist *cmd)
{
	int		op;
	t_dlist	*token;

	if (cmd == NULL)
		return (0);
	token = ((t_dlist *)(cmd->content));
	if (token == NULL)
		return (0);
	op = token->type;
	if (op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE || op == MS_TOKEN_PIPE)
		return (1);
	return (0);
}

int	ms_list(t_dlist *list)
{
	t_dlist	*pipe;

	if (NULL == list)
		return (1);
	pipe = (t_dlist *)list->content;
	pipe = pipe->next;
	while (pipe)
	{
		if (1 == ms_end_list(pipe->content))
		{
			ms_dlstcut(pipe);
			ms_dlstadd_back(&list, ms_dlstnew(pipe, pipe->type));
		}
		else if (1 == ms_end_list(pipe->prev->content))
		{
			ms_dlstcut(pipe);
			ms_dlstadd_back(&list, ms_dlstnew(pipe, MS_PARSE_LIST));
		}
		pipe = pipe->next ;
	}
	return (0);
}

