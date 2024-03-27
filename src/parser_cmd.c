/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/14 10:58:11 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "dlist.h"
/*determine l'operateur signifiant l fin d'une commande simple*/
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

/*regroupe en un noeud CMD les commandes simples*/
int	ms_cmd(t_dlist *cmd)
{
	t_dlist	*token;

	token = (t_dlist *)cmd->content;
	while (NULL != token)
	{
		if (1 == ms_end_command(token))
		{
			if (NULL == token->prev)
				cmd->type = token->type;
			else if (0 != ms_dlst_break_chain(cmd, token, token->type))
				return (1);
		}
		if (1 == ms_end_command(token->prev))
		{
			if (0 != ms_dlst_break_chain(cmd, token, MS_PARSE_CMD))
				return (1);
		}
		token = token->next ;
	}
	return (0);
}
