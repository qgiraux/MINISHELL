/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_istype_token_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:24:31 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/11 13:34:00 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

int	ms_dlist_istype_pipe_and_or(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_PIPE == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_parenthesis(t_dlist *list)
{
	if (MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_not_first(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_CLOSE == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_parse(t_dlist *list)
{
	if (MS_PARSE_CMD == list->type \
		|| MS_PARSE_PIPE == list->type || MS_PARSE_LIST == list->type \
		|| MS_PARSE_CMP == list->type)
		return (1);
	return (0);
}