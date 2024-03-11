/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:17:52 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exp_utils.h"
#include "token.h"

static int	ms_exp_curr_unescape(t_dlist **head)
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
				return (ms_e(__FILE__, __LINE__, 0), 1); //
			curr->content = str;
		}
		curr = curr->next;
	}
	return (MS_SUCCESS);
}

static int	ms_exp_curr_expand(t_dlist **head, char **env, void *data)
{
	char	*str;
	t_dlist	*curr;
	t_dlist	**ptr_curr;

	curr = *head;
	while (curr)
	{
		if (NULL == curr->content)
			curr = curr->next;
		else
		{
			str = ms_exp_parameter((char *)(curr->content), env, data);
			if (NULL == str)
				return (ms_e(__FILE__, __LINE__, 0), 1); //
			free(curr->content);
			curr->content = str;
			if (*head == curr)
				ptr_curr = head;
			else
				ptr_curr = &curr;
			if (ms_exp_filename(ptr_curr, &curr, data))
				return (ms_e(__FILE__, __LINE__, 0), 1); //
		}
	}
	return (MS_SUCCESS);
}

/* ms_exp_str:
 * Expands <str> in <exp> list
 */

int	ms_exp_str(const char *str, t_dlist **exp, void *data)
{
	char	**env;
	char	*dup;

	env = ms_env(data);
	dup = ft_strdup(str);
	if (NULL == dup)
		return (ms_perror(MS_E), 1);
	*exp = ms_dlstnew(dup, MS_TOKEN_WORD);
	if (NULL == *exp)
		return (ms_perror(MS_E), 1);
	if (ms_exp_curr_expand(exp, env, data))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (ms_exp_curr_unescape(exp))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	return (MS_SUCCESS);
}

/* ms_exp:
 * Expands <head> each member of the list
 * <$var> are replaced by <value> from environment
 * $? are replaced by exit code of previous pipe
 * * add members to the list matching the pattern (nothing done if no match)
 */

int	ms_exp(t_dlist **head, void *data)
{
	char	**env;

	env = ms_env(data);
	if (ms_exp_curr_expand(head, env, data))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (ms_exp_curr_unescape(head))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	return (MS_SUCCESS);
}
