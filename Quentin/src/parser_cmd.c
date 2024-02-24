/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/24 12:34:36 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"

int	ms_end_command(t_dlist *token_list)
{
	int	op;

	if (token_list == NULL)
		return (0);
	op = token_list->type;
	if (op == MS_TOKEN_AND || op == MS_TOKEN_OR || op == MS_TOKEN_PIPE
		|| op == MS_TOKEN_OPEN || op == MS_TOKEN_CLOSE)
		return (1);
	return (0);
}

int	ms_cmd_list(t_dlist *cmd_list)
{
	t_dlist	*token_list;

	token_list = (t_dlist *)cmd_list->content;
	token_list = token_list->next;
	while (token_list != NULL)
	{
		if (1 == ms_end_command(token_list))
		{
			ms_dlstcut(token_list);
			ms_dlstadd_back(&cmd_list, \
			ms_dlstnew(token_list, token_list->type));
		}
		else if (1 == ms_end_command(token_list->prev))
		{
			ms_dlstcut(token_list);
			ms_dlstadd_back(&cmd_list, ms_dlstnew(token_list, MS_PARSE_CMD));
		}
		token_list = token_list->next ;
	}
	return (0);
}
