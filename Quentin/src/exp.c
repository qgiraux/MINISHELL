/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/06 15:24:34 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exp_utils.h"
#include "error.h"

static int	ms_esp_curr_unescape(t_dlist **head)
{
	char	*str;
	t_dlist	*curr;

	curr = *head;
	while (curr)
	{
		if (NULL != curr->content)
		{
			str = ms_exp_escape_removal((char *)(curr->content), EXP_ESC_LIST);
			if (NULL == str)
				return (ms_error(NULL, __FILE__, __LINE__, 0), 1); //
			curr->content = str;
		}
		curr = curr->next;
	}
	return (0);
}

static int	ms_esp_curr_expand(t_dlist **head, char **env, void *data)
{
	char	*str;
	t_dlist	*curr;

	curr = *head;
	while (curr)
	{
		if (NULL == curr->content)
			curr = curr->next;
		else
		{
			str = ms_exp_parameter((char *)(curr->content), env, data);
			if (NULL == str)
				return (ms_error(NULL, __FILE__, __LINE__, 0), 1); //
			curr->content = str;
			if (ms_exp_filename(&curr, data))
				return (ms_error(NULL, __FILE__, __LINE__, 0), 1); //
		}
	}
	return (0);
}

int	ms_exp(t_dlist **head, void *data)
{
	char	**env;

	env = ms_env(data);
	if (ms_esp_curr_expand(head, env, data))
		return (1);
	if (ms_esp_curr_unescape(head))
		return (1);
	return (0);
}
