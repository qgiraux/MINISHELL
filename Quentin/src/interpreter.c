/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/22 12:51:00 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"


void	ms_interpreter(char *input)
{
	t_dlist		*token_head;
	t_dlist		*cmd_head;
	t_dlist		*pipe_head;
	t_dlist		*list_head;
	t_dlist		*list;

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
	
	token_head = ms_token_list(input, data);
		cmd_head = ms_cmd_list(token_head);
		pipe_head  = ms_pipeline(cmd_head);
		list_head =ms_list(pipe_head);
				
		list = list_head;
		while (list)
		{
			print_input(list->content, data);
			list = list->next;
			printf("\n");
		}
}

void 	print_input(t_dlist *list, const char **data)
{
	t_dlist			*token;
	int				operator;
	const char		**operator_arr = ms_token_get_operator_arr(data);
		if (list->type == -1)
		{
		token = list;
				while (token)
				{
					operator = ((t_token *)(token->content))->operator;
					if (MS_TOKEN_WORD == operator)
						ft_putstr_fd(((t_token *)(token->content))->word, 1);
					else
						ft_putstr_fd((char *)operator_arr[operator], 1);
					ft_putstr_fd(" ", 1);
					token = token->next;
				}
				return ;
		}
		while (list)
		{
			print_input(list->content, data);
			list = list->next;
		}
}
