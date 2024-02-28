/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:29:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 15:50:18 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/dlist.h"
#include "../includes/parser.h"

int	parser_error(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);
	int				i;

	i = 0;

	if (list == NULL)
		return (1);
	if (1 == ms_dlist_istype_not_first(list))
	{
		ft_putstr_fd("msh: parse error near '", 2);
		ft_putstr_fd((char *)operator_arr[list->type], 2);
				ft_putstr_fd("'\n", 2);
		return (1);
	}
	while (list != NULL)
	{
		if (MS_TOKEN_OPEN == list->type)
			i++;
		if (MS_TOKEN_CLOSE == list->type)
			i--;
		if (1 == ms_dlist_istype_operator(list) && list->type != MS_TOKEN_CLOSE)
		{
			if (list->next == NULL)
			{
				ft_putstr_fd("msh: syntax error - line ends on '", 2);
				ft_putstr_fd((char *)operator_arr[list->type], 2);
				ft_putstr_fd("'\n", 2);
				return (1);
			}
		}
		if (1 == ms_dlist_istype_pipe_and_or(list) \
		|| list->type == MS_TOKEN_OPEN)
		{
			if (1 == ms_dlist_istype_pipe_and_or(list->next) \
			|| list->next->type == MS_TOKEN_CLOSE)
			{
				ft_putstr_fd("msh: syntax error near unexpected token '", 2);
				ft_putstr_fd((char *)operator_arr[list->next->type], 2);
				ft_putstr_fd("'\n", 2);
				return (1);
			}
		}
		if (1 == ms_dlist_istype_redir(list) \
		&& 0 == ms_dlist_istype_word(list->next))
		{
			ft_putstr_fd("msh: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)operator_arr[list->next->type], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		if (MS_TOKEN_PIPE == list->type \
		&& 1 == ms_dlist_istype_parenthesis(list->prev))
		{
			ft_putstr_fd("msh: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)operator_arr[list->type], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		if (MS_TOKEN_PIPE == list->type \
		&& 1 == ms_dlist_istype_parenthesis(list->next))
		{
			ft_putstr_fd("msh: syntax error near unexpected token '", 2);
			ft_putstr_fd((char *)operator_arr[list->next->type], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		list = list->next;
	}
	if (0 != i)
		return (ft_putstr_fd("msh: parse error near ')'\n", 2), 1);
	return (0);
}
