/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 13:17:41 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"


int	ms_end_command(t_dlist *token)
{
	int	op;

	if (token == NULL)
		return (0);
	op = token->type;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR || op == MS_TOKEN_PIPE
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

int	ms_cmd_list(t_dlist *cmd_list)
{
	t_dlist	*token;

	token = cmd_list;
	token = token->next;
	while (token)
	{
		if (1 == ms_end_command(token) || 1 == ms_end_command(token->prev))
		{
			ms_dlstcut(token);
			ms_dlstadd_back(&cmd_list, ms_dlstnew(token, MS_PARSE_CMD));
		}
		token = token->next ;
	}
	return (0);
}
