/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:29:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 10:10:18 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_error.h"
#include "token.h"
#include "token_utils.h"

/*verifie que on ne commence pas sur un symbole interdit*/
static int	ms_error_start(t_dlist *list, void *data)
{
	if (list == NULL)
		return (1);
	if (1 == ms_dlist_istype_not_first(list))
		return (ms_error_write(list->type, data), 1);
	if (1 == ms_dlist_istype_redir(list))
	{
		if (NULL == list->next || 0 == ms_dlist_istype_word(list->next))
			return (ms_error_write(list->type, data), 1);
	}
	return (0);
}

/*verifie que l'emplacement des pipes par rapport aux parentheses est ok*/
static int	ms_error_pipe(t_dlist *list, void *data)
{
	if (MS_TOKEN_PIPE == list->type \
	&& (1 == ms_dlist_istype_cmpd(list->prev) || NULL == list->next))
		return (ms_error_write(list->type, data), 1);
	if (MS_TOKEN_PIPE == list->type \
	&& 1 == ms_dlist_istype_cmpd(list->next))
		return (ms_error_write(list->next->type, data), 1);
	return (0);
}

/*verifie que l'ordre des parentheses est coherent*/
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
	if (1 == ms_dlist_istype_pipe_list(list) \
	|| MS_TOKEN_OPEN == list->type)
	{
		if (1 == ms_dlist_istype_pipe_list(list->next) \
		|| MS_TOKEN_CLOSE == list->next->type)
		{
			ms_error_write(list->next->type, data);
			return (1);
		}
	}
	if (1 == ms_dlist_istype_redir(list) \
	&& 0 == ms_dlist_istype_word(list->next))
		return (ms_error_write(list->next->type, data), 1);
	return (0);
}

/*verifie que le nombre de parentheses est coherent */
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
			return (ft_putstr_fd(MS_CLOSE_PARENTH_MSG, 2), 1);
		list = list->next;
	}
	if (0 < i)
		return \
		(ft_putstr_fd(MS_OPEN_PARENTH_MSG, 2), 1);
	return (0);
}

/*verifie les erreurs de parse*/
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
	return (MS_SUCCESS);
}
