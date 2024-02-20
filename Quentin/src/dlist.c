/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/20 14:30:54 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dlist.h"

t_dlist	*ms_dlstlast(t_dlist *lst)
{
	t_dlist	*curr;

	if (NULL == lst)
		return (NULL);
	curr = lst;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_dlist	*ms_dlstfirst(t_dlist *lst)
{
	t_dlist	*curr;

	if (NULL == lst)
		return (NULL);
	curr = lst;
	while (curr->prev)
		curr = curr->prev;
	return (curr);
}

void	ms_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (NULL == lst)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	last = ms_dlstlast(*lst);
	new->prev = last;
	last->next = new;
}

void	ms_dlstcut(t_dlist *new_head)
{
	if (new_head->prev)
	{
		new_head->prev->next = NULL;
		new_head->prev = NULL;
	}
}
