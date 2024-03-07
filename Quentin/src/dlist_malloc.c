/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 16:22:20 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

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

t_dlist	*ms_dlstreplace(t_dlist **head, t_dlist **curr, t_dlist *new)
{
	t_dlist	*next;
	t_dlist	*new_last;

	if (NULL == head || NULL == *head || NULL == curr || NULL == *curr)
		return (NULL);
	next = (*curr)->next;
	if (NULL == new)
		*curr = ms_dlstremove(head, *curr);
	else
	{
		new->prev = (*curr)->prev;
		if (NULL == (*curr)->prev)
			*head = new;
		else
			(*curr)->prev->next = new;
		new_last = ms_dlstlast(new);
		new_last->next = (*curr)->next;
		if (NULL != (*curr)->next)
			(*curr)->next->prev = new_last;
		ms_dlstdelone((*curr));
		(*curr) = new_last;
	}
	return (next);
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

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (ms_dlist_istype_operator(tmp))
			;
		else if (ms_dlist_istype_word(tmp))
		{
			if (tmp->content)
				free(tmp->content);
		}
		free(tmp);
	}
	*lst = NULL;
	return ;
}

t_dlist	*ms_dlstnew(void *content, int type)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ms_dlst_break_chain(t_dlist *list, t_dlist *arg_list, int type)
{
	ms_dlstcut(arg_list);
	ms_dlstadd_back(&list, ms_dlstnew(arg_list, type));
}
