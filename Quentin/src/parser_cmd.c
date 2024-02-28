/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 16:56:42 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"


/*	regroupe les tokens par groupes separes de  '&&', '||', '|', '(' ou ')'
* 	laisse ces operateurs dans leurs propre groupes, hors des commandes simples */

static int	ms_end_command(t_dlist *token)
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

int	ms_cmd(t_dlist *cmd)
{
	t_dlist	*token;

	token = (t_dlist *)cmd->content;
	while (token != NULL)
	{
		if (1 == ms_end_command(token))
		{
			if (NULL == token->prev)
				cmd->type = token->type;
			else
			{
				ms_dlstcut(token);
				ms_dlstadd_back(&cmd, ms_dlstnew(token, token->type));
			}
		}
		if (1 == ms_end_command(token->prev))
		{
			ms_dlstcut(token);
			ms_dlstadd_back(&cmd, ms_dlstnew(token, MS_PARSE_CMD));
		}
		token = token->next ;
	}
	return (0);
}
