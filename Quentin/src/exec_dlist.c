/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:30:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

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
			return (ms_e(__FILE__, __LINE__, 1), NULL);
		curr = curr->next;
		ac++;
	}
	if (0 == ac)
		return (ms_e(__FILE__, __LINE__, 1), NULL);
	av = (char **)malloc(sizeof(char *) * (ac + 1));
	if (NULL == av)
		return (ms_perror(MS_E), NULL);
	return (ms_exec_dlist_fill_av(list, ac, av));
}
