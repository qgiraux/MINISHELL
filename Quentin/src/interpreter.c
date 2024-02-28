/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 14:33:24 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

t_dlist	*ms_interpreter(char *input, const char **data)
{
	t_dlist		*toprint;
	t_dlist		*list;
	int			status;

	list = ms_token_list(input, data);
	status = parser_error(list, data);
	if (status == 0)
	{
		list = ms_dlstnew(list, MS_PARSE_CMD);
		status = ms_cmd(list);
		toprint = list;
		printf("\nCOMMAND\n");
		while (toprint)
		{
			print_input(toprint->content, data);
			printf ("\t%d\n", toprint->type);
			toprint = toprint->next;
		}
		list = ms_dlstnew(list, MS_PARSE_PIPE);
			status = ms_pipeline(list);
			toprint = list;
			printf("\nPIPELINE\n");
			while (toprint)
			{
				print_input(toprint->content, data);
				printf ("\t%d\n", toprint->type);
				toprint = toprint->next;
			}
			while (NULL != list->next)
			{
				list = ms_dlstnew(list, MS_PARSE_LIST);
				status = ms_list(list);
				toprint = list;
				printf("\nLIST\n");
				while (toprint)
				{
					print_input(toprint->content, data);
					printf ("\t%d\n", toprint->type);
					toprint = toprint->next;
				}
				list = ms_dlstnew(list, MS_PARSE_CMP);
				status = ms_compound(list);
				printf("\nCOMPOUND\n");
				toprint = list;
				while (toprint)
				{
					print_input(toprint->content, data);
					printf ("\t%d\n", toprint->type);
					toprint = toprint->next;
				}
			}
	}
	return (list);
}
