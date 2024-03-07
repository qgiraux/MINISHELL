/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:21:18 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include "exp_utils.h"

static int	ms_exp_match_nowild(\
	char *name, char *ptrn, size_t *i_n, size_t *i_p)
{
	int	quote;
	int	esc;

	quote = 0;
	esc = 0;
	while (ptrn[*i_p] && (esc || EXP_WILD != ptrn[*i_p]))
	{
		if (ptrn[*i_p] == EXP_ESC)
			esc = 1;
		else if (!esc && (MS_QUOTE_1 == ptrn[*i_p] || MS_QUOTE_2 == ptrn[*i_p]))
			quote = ptrn[*i_p];
		else if (quote && quote == ptrn[(*i_p)])
			return ((*i_p)++, 0);
		else if (ptrn[(*i_p)] == name[(*i_n)])
		{
			(*i_n)++;
			esc = 0;
		}
		else if (ptrn[(*i_p)] != name[(*i_n)])
			return (1);
		(*i_p)++;
	}
	return (0);
}

static int	ms_exp_match_wild(char *name, char *ptrn, size_t *i_n, size_t *i_p)
{

	while (EXP_WILD == ptrn[*i_p] && EXP_WILD == ptrn[*i_p + 1])
		(*i_p)++;
	if (EXP_WILD == ptrn[*i_p])
	{
		if ('\0' == ptrn[*i_p + 1])
			return (*i_n = ft_strlen(name), *i_p = ft_strlen(ptrn), 0);
		else
		{
			(*i_p)++;
			if (EXP_ESC == ptrn[*i_p])
				(*i_p)++;
			while (name[*i_n] && name[*i_n] != ptrn[*i_p])
				(*i_n)++;
			if ('\0' == name[(*i_n)++])
				return (1);
			(*i_p)++;
		}
	}
	return (0);
}

static int	ms_exp_filename_match_add(\
	char *unescd_name, char *escd_ptrn, t_dlist **match)
{
	char	*escd_name;
	t_dlist	*new;
	size_t	i_p;
	size_t	i_n;

	i_p = 0;
	i_n = 0;
	while (unescd_name[i_n] && escd_ptrn[i_p])
	{
		if (ms_exp_match_nowild(unescd_name, escd_ptrn, &i_n, &i_p))
			return (0);
		if (ms_exp_match_wild(unescd_name, escd_ptrn, &i_n, &i_p))
			return (0);
	}
	if ('\0' == unescd_name[i_n] && '\0' == escd_ptrn[i_p])
	{
		escd_name = ms_exp_escape(unescd_name, EXP_ESC_LIST);
		if (NULL == escd_name)
			return (1); //
		new = ms_dlstnew(escd_name, MS_TOKEN_WORD);
		if (NULL == new)
			return (free(escd_name), 1); //
		ms_dlstadd_back(match, new);
	}
	return (0);
}

static int	ms_exp_filename_match(char *pattern, t_dlist **match, void *data)
{
	t_dlist	*file;
	char	*name;
	int		file_dot;
	int		pattern_dot;

	pattern_dot = ((EXP_DOT == pattern[0]) \
		|| (((MS_QUOTE_1 == pattern[0] || MS_QUOTE_2 == pattern[0]))\
			&& (EXP_DOT == pattern[1])));
	if (ms_exp_filename_list_cwd(&file, data))
		return (1); //
	while (file)
	{
		name = (char *)(file->content);
		file_dot = (EXP_DOT == name[0]);
		if (file_dot == pattern_dot)
			ms_exp_filename_match_add(name, pattern, match);
		file = file->next;
	}
	return (0);
}

int	ms_exp_filename(t_dlist **escaped_token, void *data)
{
	t_dlist	*curr;
	t_dlist	*new;
	int		quote;

	(void)data;
	curr = *escaped_token;
	quote = 0;
	if (MS_TOKEN_WORD == curr->type \
		&& ms_token_strchr(\
			(const char *)(curr->content), EXP_WILD, &quote))
	{
		new = NULL;
		if (ms_exp_filename_match(curr->content, &new, NULL)) //
			return (1);
		if (NULL != new)
		{
			*escaped_token = ms_dlstreplace(escaped_token, &curr, new);
			return (0);
		}
	}
	*escaped_token = curr->next;
	return (0);
}

// int main(int ac, char **av)
// {
// 	char	*pattern;
// 	char	*filename;
// 	t_dlist	*match;

// 	match = NULL;
// 	if (3 == ac)
// 	{
// 		filename = ft_strdup(av[1]);
// 		pattern = ft_strdup(av[2]);
// 		printf("filename:%s\tpattern:%s\n", filename, pattern);
// 		ms_exp_filename_match_add(filename, pattern, &match);
// 	}
// 	if (2 == ac)
// 	{
// 		pattern = ft_strdup(av[1]);
// 		printf("pattern:%s\n",  pattern);
// 		ms_exp_filename_match(pattern, &match, NULL);
// 		while (match)
// 		{
// 			printf("file:%s\n", (char *)(match->content));
// 			match = match->next;
// 		}
// 	}
// 	return (0);
// }
