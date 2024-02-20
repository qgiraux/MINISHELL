/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/20 18:53:59 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

char	*ms_main_prompt(void)
{
	return ("MSH > "); //
}


//

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
	const char		**operator_arr = ms_token_get_operator_arr(data);
	char		*input = "";
	t_dlist		*token;
	t_dlist		*token_head;
	t_dlist		*cmd_head;
	t_dlist		*cmd;
	t_dlist		*pipe_list;
	t_dlist		*pipe_head;
	int			operator;

	
	while (0 != ft_strncmp(input, "exit", 4))
	{
		input = readline(ms_main_prompt());
		if (NULL == input)
			return (1);
		add_history(input);
		token_head = ms_token_list(input, data);
		cmd_head = ms_cmd_list(token_head);
		pipe_head  = ms_pipeline_list(cmd_head);
		token = token_head;
		cmd = cmd_head;
		pipe_list = pipe_head;
		while (pipe_list)
		{
			cmd = (t_dlist *)pipe_list->content;
			printf("NEW PIPE : \n");
			while (cmd)
			{
				token = (t_dlist *)cmd->content;
				
				while (token)
				{
					operator = ((t_token *)(token->content))->operator;
					if (MS_TOKEN_WORD == operator)
					{
						ft_putstr_fd(((t_token *)(token->content))->word, 1);
					}
					else
					{
						ft_putstr_fd((char *)operator_arr[operator], 1);
					}
					ft_putstr_fd(" ", 1);
					token = token->next;
				}
				printf("\n");
				cmd = cmd->next;
			}
			printf("\n");
			pipe_list = pipe_list->next;
		}
	}
	free(input);
	return (0);
}
