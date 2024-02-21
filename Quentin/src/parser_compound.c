/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:48:01 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/21 16:43:44 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	ms_is_cmp(t_dlist *cmd)
{
	int		op;
	t_dlist	*token;

	if (cmd == NULL)
		return (0);
	token = ((t_dlist *)(cmd->content));
	if (token == NULL)
		return (0);
	op = ((t_token *)(token->content))->operator;
	if (op == MS_TOKEN_OPEN)
		return (1);
	if (op == MS_TOKEN_CLOSE)
		return (2);
	if (op == MS_TOKEN_PIPE || op == MS_TOKEN_AND || op == MS_TOKEN_OR)
		return (3);
	return (0);
}

t_dlist	*ms_compound(t_dlist *list)
{
	t_dlist	*cmp;
	int		c_parenthese;

	c_parenthese = 0;
	if (NULL == list)
		return (NULL);
	cmp = NULL;
	cmp = ms_dlstnew(list, MS_PARSE_CMP);
	list = list->next;
	while (list)
	{
		if (1 == ms_is_cmp(list->content) && c_parenthese == 0)
		{
			ms_dlstcut(list);
			ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP));
		}
		if (1 == ms_is_cmp(list->content) && c_parenthese != 0)
			c_parenthese++;
		if (2 == ms_is_cmp(list->content) && c_parenthese == 1)
		{
			c_parenthese--;
			ms_dlstcut(list);
			ms_dlstadd_back(&cmp, ms_dlstnew(list, MS_PARSE_CMP));
		}
		if (2 == ms_is_cmp(list->content) && c_parenthese != 1)
			c_parenthese--;
		if (c_parenthese < 0)
			return (printf("error\n"), NULL);
		list = list->next;
	}
	
	return (list);
}