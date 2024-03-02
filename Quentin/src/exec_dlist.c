/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:45 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_utils.h"

static char	**ms_exec_dlist_fill_av(t_dlist *list, int ac, char **av)
{
	int	i;

	i = 0;
	while (list && i < ac)
	{
		av[i++] = list->content;
		list = list->next;
	}
	av[i] = NULL;
	return (av);
}

char	**ms_exec_dlist_to_av(t_dlist *list)
{
	int		ac;
	t_dlist	*curr;
	char	**av;

	ac = 0;
	curr = list;
	while (curr)
	{
		if (MS_TOKEN_WORD != curr->type || NULL == curr->content)
			return (ms_exec_error((void *)__FILE__, MS_EUNKNWN, 2, NULL), NULL);
		curr = curr->next;
		ac++;
	}
	if (0 == ac)
		return (ms_exec_error((void *)__FILE__, MS_EUNKNWN, 2, NULL), NULL);
	av = (char **)malloc(sizeof(char *) * (ac + 1));
	if (NULL == av)
		return (ms_exec_error(NULL, errno, 2, NULL), NULL);
	return (ms_exec_dlist_fill_av(list, ac, av));
}
