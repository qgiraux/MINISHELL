/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_start_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:58:35 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 16:21:31 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/dlist.h"
#include "../includes/node_type.h"
#include "../includes/msh_utils.h"

/*donne un prompt, lance le parse, puis execute l'arbre logique */
int	ms_start_loop(char **data, char *input)
{
	t_dlist *list;

	input = readline(MSH);
		add_history(input);
		if (NULL == input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			return(1);
		}
		list = ms_interpreter(input, data);
		if (NULL != list)
		{
			ms_node_type(list, 0, data);
		}
		free(input);
		//ms_free_input(list);
		return (0);
}