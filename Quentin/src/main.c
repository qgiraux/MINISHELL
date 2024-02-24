/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/24 12:43:48 by qgiraux          ###   ########.fr       */
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
	t_dlist		*token_head;
	t_dlist		*cmd_head;
	t_dlist		*pipe_head;
	t_dlist		*list_head;
	t_dlist		*list;
	t_dlist		*cmp_head;
	int			status = 0;

	input = "";
	while (1)
	{
		input = readline(ms_main_prompt());
		add_history(input);
		if (input == NULL || ft_strncmp(input, "exit", 4) == 0)
			break ;
		token_head = ms_token_list(input, data);
		if (token_head == NULL)
			return (printf("error\n"), 1);
		status = parser_error(token_head, data);
		if (status == 0)
		{
			cmd_head = ms_dlstnew(token_head, MS_PARSE_CMD);
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
			pipe_head = ms_dlstnew(cmd_head, MS_PARSE_PIPE0);
			status = ms_pipeline(pipe_head);
			list = pipe_head;
			printf ("\n PIPE LIST :\n");
			while (list)
			{
				print_input((t_dlist *)list->content, data);
				list = list->next;
				printf("\n");
			}
			list_head = ms_dlstnew(pipe_head, MS_PARSE_LIST);
			status = ms_list(list_head);
			list = list_head;
			printf ("\n LISTE LIST :\n");
			while (list)
			{
				print_input((t_dlist *)list->content, data);
				list = list->next;
				printf("\n");
			}
			cmp_head = ms_dlstnew(list_head, MS_PARSE_CMP0);
			status = ms_compound(cmp_head);
			if (status != 0)
				return (1);
			list = cmp_head;
			printf ("\n COMPOUND LIST :\n");
			while (list != NULL)
			{
				print_input((t_dlist *)list->content, data);
				list = list->next;
				printf("\n");
			}
		}
		free_input(cmp_head);
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
		ft_putstr_fd(" ", 1);
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
