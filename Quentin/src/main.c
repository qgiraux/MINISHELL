/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/27 15:49:34 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/dlist.h"

char	*ms_main_prompt(void)
{
	return ("MSH > ");
}

int	main(void)
{
	const char	*data[10] = {\
	MS_CONTROL_PIPE,
	MS_CONTROL_AND, \
	MS_CONTROL_OR, \
	MS_CONTROL_OPEN, \
	MS_CONTROL_CLOSE, \
	MS_REDIR_INTPUT, \
	MS_REDIR_OUTPUT, \
	MS_REDIR_APPEND, \
	MS_REDIR_HERE_DOC, \
	NULL};
	char		*input;

	t_dlist		*list;

	input = "";
	while (1)
	{
		input = readline(ms_main_prompt());
		add_history(input);
		if (input == NULL || ft_strncmp(input, "exit", 4) == 0)
			break ;
		list = ms_interpreter(input, data);
		
		while (list)
			{
				print_input((t_dlist *)list->content, data);
				printf("\t%d", list->type);
				list = list->next;
				printf("\n");
			}
		free_input(list);
	}
	rl_clear_history();
	free(input);
	return (0);
}






void	print_input(t_dlist *list, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	while (list != NULL)
	{
		if (list->type == -1)
			ft_putstr_fd((char *)(list->content), 1);
		else if (list->content == NULL)
			ft_putstr_fd((char *)operator_arr[list->type], 1);
		else
			print_input(list->content, data);
		ft_putstr_fd("", 1);
		list = list->next;
	}
}

void	free_input(t_dlist *list)
{
	t_dlist	*tmp;

	while (list != NULL)
	{
		if (list->content == NULL || list->type == -1)
		{
			tmp = list->next;
			if (list->type == -1)
				free(list->content);
			free(list);
			list = tmp;
		}
		else
		{
			free_input(list->content);
			list = list->next;
		}
	}
}
