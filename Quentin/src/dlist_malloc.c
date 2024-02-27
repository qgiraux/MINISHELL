/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 10:49:35 by qgiraux          ###   ########.fr       */
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
	t_dlist	*next;
	t_dlist	*tmp;

	lst = lst->next;
	tmp = lst;
	next = tmp->next;
	if (next != NULL)
		next->prev = NULL;
	//free_input(tmp->content);
	free (tmp);
	tmp = NULL;
	return (next);
}
