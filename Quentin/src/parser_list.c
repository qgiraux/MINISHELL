/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:00:24 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 14:48:54 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_dlist	*ms_list_isitlist(t_dlist *pipe, t_dlist *list)
{
	if (1 == ms_dlist_istype_parenthesis(pipe))
	{
		if (pipe->prev)
		{
			ms_dlstcut(pipe);
			ms_dlstadd_back(&list, ms_dlstnew(pipe, pipe->type));				
		}
		else
			list->type = pipe->type;
	}
	if (pipe->prev && 1 == ms_dlist_istype_parenthesis(pipe->prev))
	{
		ms_dlstcut(pipe);
		if (1 == ms_dlist_istype_pipe_and_or(pipe))
			ms_dlstadd_back(&list, ms_dlstnew(pipe, pipe->type));
		else
			ms_dlstadd_back(&list, ms_dlstnew(pipe, MS_PARSE_LIST));
		
	}
	if (1 == ms_dlist_istype_pipe_and_or(pipe))
	{
		if (1 == ms_dlist_istype_parenthesis(pipe->next))
		{
			ms_dlstcut(pipe);
			ms_dlstadd_back(&list, ms_dlstnew(pipe, pipe->type));
		}
	}
	return (pipe->next);
}

int	ms_list(t_dlist *list)
{
	t_dlist	*pipe;

	if (NULL == list)
		return (1);
	pipe = (t_dlist *)list->content;
	while (pipe)
		pipe = ms_list_isitlist(pipe, list);
	return (0);
}
