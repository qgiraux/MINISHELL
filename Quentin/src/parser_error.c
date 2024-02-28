/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:29:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 16:16:25 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"
#include "../includes/token.h"

static int	ms_error_start(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	if (list == NULL)
		return (1);
	if (1 == ms_dlist_istype_not_first(list))
	{
		ft_putstr_fd("MSH: parse error near '", 2);
		ft_putstr_fd((char *)operator_arr[list->type], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

static int	ms_error_pipe(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	if (MS_TOKEN_PIPE == list->type \
	&& 1 == ms_dlist_istype_parenthesis(list->prev))
	{
		ft_putstr_fd("MSH: syntax error near unexpected token '", 2);
		ft_putstr_fd((char *)operator_arr[list->type], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (MS_TOKEN_PIPE == list->type \
	&& 1 == ms_dlist_istype_parenthesis(list->next))
	{
		ft_putstr_fd("MSH: syntax error near unexpected token '", 2);
		ft_putstr_fd((char *)operator_arr[list->next->type], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

static int	ms_error_parenthesis(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	if (1 == ms_dlist_istype_operator(list) && MS_TOKEN_CLOSE != list->type)
	{
		if (list->next == NULL)
		{
			ft_putstr_fd("MSH: syntax error - line ends on '", 2);
			ft_putstr_fd((char *)operator_arr[list->type], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	if (1 == ms_dlist_istype_pipe_and_or(list) \
	|| MS_TOKEN_OPEN == list->type)
	{
		if (1 == ms_dlist_istype_pipe_and_or(list->next) \
		|| MS_TOKEN_CLOSE == list->next->type)
		{
			ft_putstr_fd("MSH: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)operator_arr[list->next->type], 2);
			ft_putstr_fd("'\n", 2);
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
		list = list->next;
	}
	if (0 > i)
		return (ft_putstr_fd("MSH: parse error near ')'\n", 2), 1);
	if (0 < i)
		return (ft_putstr_fd("MSH: syntax error unclosed parenthesis:(\n", 2), 1);
	return (0);
}

int	ms_parser_error(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	if (0 != ms_error_start(list, data) \
	|| 0 != ms_error_nb_parenthesis(list))
		return (1);
	while (list != NULL)
	{
		if (1 == ms_dlist_istype_redir(list) \
		&& 0 == ms_dlist_istype_word(list->next))
		{
			ft_putstr_fd("MSH: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)operator_arr[list->next->type], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		if (0 != ms_error_pipe(list, data) \
		|| 0 != ms_error_parenthesis(list, data))
			return (1);
		list = list->next;
	}
	return (0);
}
