/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/24 12:35:31 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dlist.h"
#include "../includes/minishell.h"

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
	return (node);
}

t_dlist	*ms_dlst_free_link(t_dlist *lst)
{
	t_dlist	*previous;
	t_dlist	*next;
	t_dlist	*tmp;

	tmp = lst;
	previous = tmp->prev;
	next = tmp->next;
	if (previous != NULL)
		previous->next = next;
	else if (next != NULL)
		next->prev = previous;
	free_input(tmp->content);
	free (tmp);
	tmp = NULL;
	return (next);
}
