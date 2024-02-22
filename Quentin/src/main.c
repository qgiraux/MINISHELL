/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/22 12:51:53 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

void 	free_input(t_dlist *list);

char	*ms_main_prompt(void)
{
	return ("MSH > "); //
}

int	main(void)
{
	char		*input = "";
	
	while (0 != ft_strncmp(input, "exit", 4))
	{
		input = readline(ms_main_prompt());
		add_history(input);
		ms_interpreter(input);
		free (input);		
	}
	free(input);
	return (0);
}



void 	free_input(t_dlist *list)
{
	t_dlist			*token;
		if (list->type == -1)
		{
			while (list)
			{
				token = list->next;
				free (list->content);
				free (list);
				list = token;
				list = list->next;
			}
			return ;
		}
		while (list)
		{
			free_input(list->content);
			list = list->next;
		}
}