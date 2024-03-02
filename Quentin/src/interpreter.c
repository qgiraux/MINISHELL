/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:44 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/02 14:26:38 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/node_type.h"

t_dlist	*ms_interpreter(char *input, const char **data)
{
	t_dlist		*list;
	int			status;
	//t_dlist		*toprint;

	status = 0;
	list = ms_token_list(input, data);
	if (0 == ms_parser_error(list, data))
	{
		list = ms_dlstnew(list, MS_PARSE_CMD);
		if (NULL == list)
			return (NULL);
		status += ms_cmd(list);
		/*toprint = list;
		printf("\nCMD\n");
		while (toprint)
		{
			print_input(toprint->content, data);
			printf("\t%d", toprint->type);
			toprint = toprint->next;
			printf("\n");
		}*/
		list = ms_dlstnew(list, MS_PARSE_PIPE);
		if (NULL == list)
			return (NULL);
		status += ms_pipeline(list);
		/*toprint = list;
		printf("\nPIPE\n");
		while (toprint)
		{
			print_input(toprint->content, data);
			printf("\t%d", toprint->type);
			toprint = toprint->next;
			printf("\n");
		}*/
		while (NULL != list->next || 0 != status)
		{
			list = ms_dlstnew(list, MS_PARSE_LIST);
			if (NULL == list)
			return (NULL);
			status += ms_list(list);
			/*toprint = list;
			printf("\nLIST\n");
			while (toprint)
			{
				print_input(toprint->content, data);
				printf("\t%d", toprint->type);
				toprint = toprint->next;
				printf("\n");
			}*/
			if (NULL == list->next || 0 != status)
				return (list);
			list = ms_dlstnew(list, MS_PARSE_CMP);
			if (NULL == list)
			return (NULL);
			status += ms_compound(list);
			/*toprint = list;
			printf("\nCOMPOUND\n");
			while (toprint)
			{
				print_input(toprint->content, data);
				printf("\t%d", toprint->type);
				toprint = toprint->next;
				printf("\n");
			}*/
		}
	}
	
	return (list);
}
