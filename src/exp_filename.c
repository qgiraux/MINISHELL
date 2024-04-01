/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/04/01 16:25:20 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token.h"
#include "exp_utils.h"

static int	_match_madd(char *unescd_name, char *escd_ptrn, t_dlist **match)
{
	char	*escd_name;
	t_dlist	*new;
	size_t	i_p;
	size_t	i_n;

	i_p = 0;
	i_n = 0;
	while (unescd_name[i_n] || escd_ptrn[i_p])
	{
		if (0 == exp_filename_wild_match(unescd_name, escd_ptrn, &i_n, &i_p))
			return (MS_SUCCESS);
		else if (0 == i_p && 0 == i_n)
			return (ms_e(__FILE__, __LINE__, 1), 1);
	}
	if ('\0' == unescd_name[i_n] && '\0' == escd_ptrn[i_p])
	{
		escd_name = ms_exp_escape_dup(unescd_name, EXP_ESC_LIST);
		if (NULL == escd_name)
			return (ms_e(__FILE__, __LINE__, 0), 1);
		new = ms_dlstnew(escd_name, MS_TOKEN_WORD);
		if (NULL == new)
			return (ms_e(__FILE__, __LINE__, 0), free(escd_name), 1);
		ms_dlstadd_back(match, new);
	}
	return (MS_SUCCESS);
}

static int	_match_madd_cwd(char *pattern, t_dlist **match, void *data)
{
	t_dlist	*file;
	char	*name;
	int		file_dot;
	int		pattern_dot;

	pattern_dot = ((EXP_DOT == pattern[0]) \
		|| (((MS_QUOTE_1 == pattern[0] || MS_QUOTE_2 == pattern[0])) \
			&& (EXP_DOT == pattern[1])));
	if (ms_exp_filename_list_cwd(data))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	file = ms_data_files_get(data);
	while (file)
	{
		name = (char *)(file->content);
		file_dot = (EXP_DOT == name[0]);
		if (file_dot == pattern_dot)
		{
			if (_match_madd(name, pattern, match))
				return (ms_e(__FILE__, __LINE__, 0), 1);
		}
		file = file->next;
	}
	return (MS_SUCCESS);
}

int	ms_exp_filename(t_dlist **escpd_token, t_dlist **next, void *data)
{
	t_dlist	*curr;
	t_dlist	*new;
	int		quote;

	curr = *escpd_token;
	quote = 0;
	if (MS_TOKEN_WORD == curr->type \
		&& ms_token_strchr(\
			(const char *)(curr->content), EXP_WILD, &quote))
	{
		new = NULL;
		if (_match_madd_cwd(curr->content, &new, data))
			return (ms_e(__FILE__, __LINE__, 0), \
				ms_dlstclear(&new), 1);
		if (NULL != new)
		{
			*next = ms_dlstreplace(escpd_token, &curr, new);
			return (MS_SUCCESS);
		}
	}
	*next = curr->next;
	return (MS_SUCCESS);
}
