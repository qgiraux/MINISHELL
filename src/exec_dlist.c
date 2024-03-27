/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:14:41 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

static char	**_fill_av(t_dlist **list, int ac, char **av)
{
	t_dlist	*curr;
	t_dlist	*next;
	int		i;

	curr = *list;
	i = 0;
	while (curr && i < ac)
	{
		next = curr->next;
		av[i++] = curr->content;
		free(curr);
		curr = next;
	}
	av[i] = NULL;
	*list = NULL;
	return (av);
}

int	ms_exec_dlist_to_av(t_dlist **list, char ***av)
{
	int		ac;
	t_dlist	*curr;

	*av = NULL;
	ac = 0;
	curr = *list;
	while (curr)
	{
		if (MS_TOKEN_WORD != curr->type || NULL == curr->content)
			return (ms_e(__FILE__, __LINE__, 1), ms_dlstclear(list), 1);
		curr = curr->next;
		ac++;
	}
	if (0 == ac)
		return (MS_SUCCESS);
	*av = (char **)malloc(sizeof(char *) * (ac + 1));
	if (NULL == *av)
		return (ms_perror(MS_E), ms_dlstclear(list), 1);
	*av = _fill_av(list, ac, *av);
	return (MS_SUCCESS);
}
