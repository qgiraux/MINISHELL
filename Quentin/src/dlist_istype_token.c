/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_istype_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:24:31 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/28 15:43:51 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int	ms_dlist_istype_word_only(t_dlist *list)
{
	while (list)
	{
		if (MS_TOKEN_WORD != list->type)
			return (0);
		list = list->next;
	}
	return (1);
}

int	ms_dlist_istype_word(t_dlist *list)
{
	if (MS_TOKEN_WORD == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_redir(t_dlist *list)
{
	if (MS_TOKEN_INTPUT == list->type || MS_TOKEN_OUTPUT == list->type \
		|| MS_TOKEN_APPEND == list->type || MS_TOKEN_HERE_DOC == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_token(t_dlist *list)
{
	if (MS_TOKEN_WORD == list->type || MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type \
		|| MS_TOKEN_INTPUT == list->type || MS_TOKEN_OUTPUT == list->type \
		|| MS_TOKEN_APPEND == list->type || MS_TOKEN_HERE_DOC == list->type \
		)
		return (1);
	return (0);
}

int	ms_dlist_istype_operator(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type \
		|| MS_TOKEN_INTPUT == list->type || MS_TOKEN_OUTPUT == list->type \
		|| MS_TOKEN_APPEND == list->type || MS_TOKEN_HERE_DOC == list->type \
		)
		return (1);
	return (0);
}

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
