/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:30 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/15 15:37:25 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	prep(t_elements *element, char *input, int *i, int *j)
{
	element->operation = separator(input, *i);
	if (element->operation != 0)
		*i = *i + 2;
	*j = 0;
}

t_list	*parser(char *input)
{
	int			i;
	int			j;
	t_list		*first;
	t_elements	*element;

	first = NULL;
	i = 0;
	while (input[i])
	{
		element = (t_elements *)malloc(sizeof(t_elements));
		if (!element)
			return (NULL);
		prep(element, input, &i, &j);
		while (separator(input, i + j) == 0 && input[i + j])
		{
			if (skip_quotes(input, i + j) == -1)
				return (NULL);
			j = j + skip_quotes(input, i + j);
		}
		element->element = ft_substr(input, i, j);
		ft_lstadd_back(&first, ft_lstnew(element));
		i = i + j;
	}
	return (first);
}

int	skip_quotes(char *input, int i)
{
	int	j;

	if (input[i] == '"' || input[i] == 39)
	{
		j = 1;
		while (input[i + j] != input[i])
		{
			j++;
			if (!input[i + j])
				return (-1);
		}
		return (j + 1);
	}
	return (1);
}

int	separator(char *input, int i)
{
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	if (input[i] == '|' && input[i + 1] == '|')
		return (2);
	return (0);
}

void	free_list(t_list *first)
{
	t_list		*next;
	t_elements	*elem;

	while (first != NULL)
	{
		elem = first->content;
		free (elem->element);
		free (first->content);
		next = first->next;
		free(first);
		first = next;
		return ;
	}
}
