/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/22 10:40:20 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
	op = ((t_token *)(token->content))->operator;
	if (op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE || op == MS_TOKEN_PIPE)
		return (1);
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR)
		return (2);
	return (0);
}

t_dlist	*ms_list(t_dlist *pipe)
{
	t_dlist	*list;

	if (NULL == pipe)
		return (NULL);
	list = NULL;
	list = ms_dlstnew(pipe, MS_PARSE_LIST);
	pipe = pipe->next;
	while (pipe)
	{
		if (1 == ms_end_list(pipe->content) || 1 == ms_end_list(pipe->prev->content))
		{
			ms_dlstcut(pipe);
			ms_dlstadd_back(&list, ms_dlstnew(pipe, MS_PARSE_LIST));
		}
		
		else if (2 == ms_end_list(pipe->content) && 2 == ms_end_list(pipe->next->content))
			return (printf("error  in list\n"), NULL);
		pipe = pipe->next ;
	}
	return (list);
}*/