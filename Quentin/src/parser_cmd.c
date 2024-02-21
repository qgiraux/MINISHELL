/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/21 16:20:00 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_check_doubles(t_dlist *token)
{
	int		operator;
	int		p_operator;

	if (NULL == token->next)
		return (0);
	operator = ((t_token *)(token->content))->operator;
	p_operator = ((t_token *)(token->next->content))->operator;
	if (operator == MS_TOKEN_AND || operator == MS_TOKEN_OR
		|| operator == MS_TOKEN_PIPE)
		if (p_operator == MS_TOKEN_AND || p_operator == MS_TOKEN_OR
			|| p_operator == MS_TOKEN_PIPE)
			return (1);
	return (0);
}

int	ms_end_command(t_dlist *token)
{
	int	op;

	if (token == NULL)
		return (0);
	op = ((t_token *)(token->content))->operator;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR || op == MS_TOKEN_PIPE
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

t_dlist	*ms_cmd_list(t_dlist *token)
{
	t_dlist	*cmd_list;

	if (NULL == token)
		return (NULL);
	cmd_list = NULL;
	cmd_list = ms_dlstnew(token, MS_PARSE_CMD);
	token = token->next;
	while (token)
	{
		if (1 == ms_end_command(token) || 1 == ms_end_command(token->prev))
		{
			if (1 == ms_check_doubles(token))
				return (printf("error  in cmd\n"), NULL);
			ms_dlstcut(token);
			ms_dlstadd_back(&cmd_list, ms_dlstnew(token, MS_PARSE_CMD));
		}
		token = token->next ;
	}
	return (cmd_list);
}
