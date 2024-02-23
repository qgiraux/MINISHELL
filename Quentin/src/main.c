/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 15:49:40 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/dlist.h"

void 	free_input(t_dlist *list);
void 	print_input(t_dlist *list, const char **data);

char	*ms_main_prompt(void)
{
	return ("MSH > "); //
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
	char		*input = "";
	t_dlist		*token_head;
	t_dlist		*cmd_head;
	t_dlist		*pipe_head;
	t_dlist		*list_head;
	t_dlist		*list;
//	t_dlist		*cmp_head;
	int			status = 0;

	
	while (0 != ft_strncmp(input, "exit", 4) && input != NULL)
	{
		input = readline(ms_main_prompt());
		add_history(input);
		token_head = ms_token_list(input, data);
		if (token_head == NULL)
			return (printf("error\n"), 1);
		
		cmd_head = ms_dlstnew(token_head, 101);
		status = ms_cmd_list(cmd_head);
		if (status != 0)
			return (printf("error\n"), 1);
		
		list = cmd_head;
		printf ("\nCOMMAND LIST :\n");
		while (list)
		{
			print_input((t_dlist *)list->content, data);
			list = list->next;
			printf("\n");
		}
		
		pipe_head = ms_dlstnew(cmd_head, 102);
		status = ms_pipeline(pipe_head);
		

		list = pipe_head;
		printf ("\n PIPE LIST :\n");
		while (list)
		{
			print_input((t_dlist *)list->content, data);
			list = list->next;
			printf("\n");
		}
		
		list_head = ms_dlstnew(pipe_head, 103);
		status = ms_list(list_head);

		//cmp_head = ms_dlstnew(list_head, 104);
		//status = ms_compound(cmp_head);
		//if (status != 0)
		//	return (printf("error\n"), 1);
			
		list = list_head;
		printf ("\n LISTE LIST :\n");
		while (list)
		{
			
			print_input((t_dlist *)list->content, data);
			list = list->next;
			printf("\n");
		}
		free_input(list);
		
	}
	rl_clear_history();
	free(input);
	return (0);
}

void 	print_input(t_dlist *list, const char **data)
{
	t_dlist			*token;
	int				operator;
	const char		**operator_arr = ms_token_get_operator_arr(data);
	

	if (list == NULL)
		return ;
	if (1 == ms_dlist_istype_token(list))
	{
	token = list;
		while (token)
		{
			operator = (token->type);
			if (MS_TOKEN_WORD == operator)
				ft_putstr_fd((char *)(token->content), 1);
			else
				ft_putstr_fd((char *)operator_arr[operator], 1);
			ft_putstr_fd(" ", 1);
			token = token->next;
		}
			return ;
	}
	while (list)
	{
		print_input((t_dlist *)list->content, data);
		list = list->next;
	}
}

void 	free_input(t_dlist *list)
{
	t_dlist			*token;

	if (list == NULL)
		return ;
	if (list->type == -1)
	{
			while (list)
			{
				token = list->next;	
				free (list->content);
				list = token;
			}
			return ;
	}
	while (list)
	{
		free_input(list->content);
		list = list->next;
	}
}