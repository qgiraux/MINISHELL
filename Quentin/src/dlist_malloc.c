/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/21 12:02:33 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dlist.h"

void	ms_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (del)
			del(tmp->content);
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
	node->next = NULL;
	node->type = type;
	return (node);
}
