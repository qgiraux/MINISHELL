/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 11:02:29 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"
#include "error.h"
#include "libft.h"
#include "here.h"

static t_dlist	*ms_dlstreplace_non_null(\
	t_dlist **head, t_dlist **curr, t_dlist *new)
{
	t_dlist	*to_clear;
	t_dlist	*new_last;
	t_dlist	*next;

	to_clear = *curr;
	next = to_clear->next;
	new_last = ms_dlstlast(new);
	new->prev = to_clear->prev;
	new_last->next = to_clear->next;
	if (NULL != to_clear->next)
		to_clear->next->prev = new_last;
	if (NULL == to_clear->prev)
		*head = new;
	else
		to_clear->prev->next = new;
	to_clear->prev = NULL;
	to_clear->next = NULL;
	ms_dlstclear(&to_clear);
	*curr = new_last;
	return (next);
}

t_dlist	*ms_dlstreplace(t_dlist **head, t_dlist **curr, t_dlist *new)
{
	t_dlist	*next;

	if (NULL == head || NULL == *head || NULL == curr || NULL == *curr)
		return (NULL);
	if (*curr == new)
		return ((*curr)->next);
	if (NULL == new)
	{
		next = (*curr)->next;
		*curr = ms_dlstremove(head, *curr);
		return (next);
	}
	return (ms_dlstreplace_non_null(head, curr, new));
}

t_dlist	*ms_dlstremove(t_dlist **head, t_dlist *curr)
{
	t_dlist	*tmp;

	if (NULL == head || NULL == *head || NULL == curr)
		return (NULL);
	tmp = curr->next;
	if (NULL == curr->prev)
		*head = curr->next;
	else
		curr->prev->next = curr->next;
	ms_dlstdelone(curr);
	return (tmp);
}

void	ms_dlstdelone(t_dlist *curr)
{
	if (NULL == curr)
		return ;
	if (ms_dlist_istype_operator(curr))
		;
	else if (ms_dlist_istype_word(curr))
	{
		if (curr->content)
			free(curr->content);
	}
	free(curr);
	return ;
}

void	ms_dlstclear(t_dlist **lst)
{
	t_dlist	*tmp;

	if (NULL == lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (1 == ms_dlist_istype_parse(tmp))
			ms_dlstclear((t_dlist **)&tmp->content);
		else if (1 == ms_dlist_istype_operator(tmp))
		{
			if (NULL != tmp->content)
			{
				ms_dlstclear((t_dlist **)&tmp->content);
			}
		}
		else if (NULL != tmp->content)
			free(tmp->content);
		free(tmp);
	}
	*lst = NULL;
	return ;
}
