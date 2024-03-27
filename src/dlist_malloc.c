/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/22 10:07:28 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "dlist.h"

t_dlist	*ms_dlstnew(void *content, int type)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (NULL == node)
		return (ms_perror(MS_E), NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	ms_dlst_break_chain(t_dlist *list, t_dlist *arg_list, int type)
{
	t_dlist	*new;

	ms_dlstcut(arg_list);
	new = ms_dlstnew(arg_list, type);
	if (NULL == new)
		return (ms_dlstclear(&list), 1);
	ms_dlstadd_back(&list, new);
	return (0);
}

//Malloc proofread
