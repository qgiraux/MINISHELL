/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 16:21:13 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_utils.h"
#include "dlist.h"


int	main(void)
{
	char		*data[10];
	int			result;
	
	result = 0;
	data[0] = MS_CONTROL_PIPE;
	data[1] = MS_CONTROL_AND;
	data[2] = MS_CONTROL_OR;
	data[3] = MS_CONTROL_OPEN;
	data[4] = MS_CONTROL_CLOSE;
	data[5] = MS_REDIR_INTPUT;
	data[6] = MS_REDIR_OUTPUT;
	data[7] = MS_REDIR_APPEND;
	data[8] = MS_REDIR_HERE_DOC;
	data[9] = NULL;
	while (0 == result)
	{
		result = ms_start_loop(data, "");
	}
	rl_clear_history();
	return (0);
}

/*free le memoire attribuee a l'arbre logique*/
void	ms_free_input(t_dlist *list)
{
	t_dlist	*tmp;

	while (NULL != list)
	{
		tmp = list->next;
		if (NULL == list->content || 0 == ms_dlist_istype_parse(list))
		{
			if (MS_TOKEN_WORD == list->type)
				free(list->content);
		}
		else
			ms_free_input(list->content);
		free(list);
		list = tmp;
	}
}