/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 13:43:15 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/dlist.h"
#include "../includes/node_type.h"

int	main(void)
{
	const char	*data[10] = {\
	MS_CONTROL_PIPE, MS_CONTROL_AND, MS_CONTROL_OR, \
	MS_CONTROL_OPEN, MS_CONTROL_CLOSE, MS_REDIR_INTPUT, \
	MS_REDIR_OUTPUT, MS_REDIR_APPEND, MS_REDIR_HERE_DOC, \
	NULL};
	char		*input;
	t_dlist		*list;

	input = "";
	while (1)
	{
		input = readline("Minishell >");
		add_history(input);
		if (NULL == input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		list = ms_interpreter(input, data);
		if (NULL != list)
		{
			node_type(list, 0, data);
			free_input(list);
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}

void	free_input(t_dlist *list)
{
	t_dlist	*tmp;

	while (NULL != list)
	{
		tmp = list->next;
		if (NULL == list->content || MS_TOKEN_WORD == list->type)
		{
			if (MS_TOKEN_WORD == list->type)
				free(list->content);
		}
		else
			free_input(list->content);
		free(list);
		list = tmp;
	}
}
