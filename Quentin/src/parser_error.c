/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:29:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 15:24:52 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser_error.h"
#include "../includes/token.h"
#include "../includes/token_utils.h"

static int	ms_error_start(t_dlist *list, void *data)
{
	if (list == NULL)
		return (1);
	if (1 == ms_dlist_istype_not_first(list))
		return (ms_error_write(list->type, data), 1);
	return (0);
}

static int	ms_error_pipe(t_dlist *list, void *data)
{
	if (MS_TOKEN_PIPE == list->type \
	&& (1 == ms_dlist_istype_parenthesis(list->prev) || NULL == list->next))
		return (ms_error_write(list->type, data), 1);
	if (MS_TOKEN_PIPE == list->type \
	&& 1 == ms_dlist_istype_parenthesis(list->next))
		return (ms_error_write(list->next->type, data), 1);
	return (0);
}

static int	ms_error_parenthesis(t_dlist *list, void *data)
{
	if (1 == ms_dlist_istype_operator(list) && MS_TOKEN_CLOSE != list->type)
	{
		if (list->next == NULL)
		{
			ms_error_write(list->type, data);
			return (1);
		}
	}
	if (1 == ms_dlist_istype_pipe_and_or(list) \
	|| MS_TOKEN_OPEN == list->type)
	{
		if (1 == ms_dlist_istype_pipe_and_or(list->next) \
		|| MS_TOKEN_CLOSE == list->next->type)
		{
			ms_error_write(list->next->type, data);
			return (1);
		}
	}
	return (0);
}

static int	ms_error_nb_parenthesis(t_dlist *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		if (MS_TOKEN_OPEN == list->type)
			i++;
		if (MS_TOKEN_CLOSE == list->type)
			i--;
		if (0 > i)
			(ft_putstr_fd(MS_CLOSE_PARENTH_MSG, 2));
		list = list->next;
	}
	if (0 < i)
		return \
		(ft_putstr_fd(MS_OPEN_PARENTH_MSG, 2), 1);
	return (0);
}

int	ms_parser_error(t_dlist *list, void *data)
{
	if (0 != ms_error_start(list, data) \
	|| 0 != ms_error_nb_parenthesis(list))
		return (1);
	while (list != NULL)
	{
		if (1 == ms_dlist_istype_redir(list) \
		&& 0 == ms_dlist_istype_word(list->next))
		{
			ms_error_write(list->next->type, data);
			return (1);
		}
		if (0 != ms_error_pipe(list, data) \
		|| 0 != ms_error_parenthesis(list, data))
			return (1);
		list = list->next;
	}
	return (0);
}
