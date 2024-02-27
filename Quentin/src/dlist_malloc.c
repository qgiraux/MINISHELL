/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 16:33:10 by qgiraux          ###   ########.fr       */
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
	node->prev = NULL;
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
	free (tmp);
	tmp = NULL;
	return (next);
}

void	ms_dlst_break_chain(t_dlist *list, t_dlist *arg_list, int type)
{
	ms_dlstcut(arg_list);
	ms_dlstadd_back(&list, ms_dlstnew(arg_list, type));
}
