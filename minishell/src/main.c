/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/15 15:25:23 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*input;
	t_list		*first;
	t_list		*node;
	t_elements	*elem;

	rl_initialize();
	input = readline("MSH > ");
	first = parser(input);
	if (first == NULL)
		printf("error");
	node = first;
	while (first)
	{
		elem = first->content;
		printf("%s\n", (elem->element));
		first = first->next;
	}
	free (input);
	free_list(node);
	return (0);
}
