/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/08 12:51:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "exp_utils.h"

static void	ms_exp_var_len_none(char *s, size_t *len, int *type)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return ;
	i = 0;
	while (s[i] && MS_QUOTE_1 != s[i] && MS_QUOTE_2 != s[i] && EXP_VAR != s[i])
		i++;
	if (0 != i)
		*type = MS_PARA_STR;
	*len = i;
}

static void	ms_exp_var_len_quote1(char *s, size_t *len, int *type)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return ;
	i = 0;
	if (MS_QUOTE_1 == s[0])
		i++;
	else
		return ;
	while (s[i] && MS_QUOTE_1 != s[i])
		i++;
	if (0 == i)
		return ;
	if (MS_QUOTE_1 == s[i])
	{
		*type = MS_PARA_QUOTE1;
		*len = i + 1;
	}
	else
		*type = MS_PARA_ERROR; //
}

static void	ms_exp_var_len_quote2(char *s, size_t *len, int *type)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return ;
	i = 0;
	if (MS_QUOTE_2 == s[0])
		i++;
	else
		return ;
	*type = MS_PARA_QUOTE2;
	*len = i;
}

static void	ms_exp_var_len_esc(char *s, size_t *len, int *type)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return ;
	i = 0;
	if (EXP_ESC == s[0])
		i++;
	else
		return ;
	*type = MS_PARA_ESC;
	*len = i;
}

int	ms_parameter_quote(char *s, size_t *len, int *type)
{
	if (NULL == s || '\0' == *s)
		return (1);
	*len = 0;
	if (EXP_VAR == s[0])
		return (0);
	ms_exp_var_len_quote1(s, len, type);
	if (0 != *len)
		return (0);
	ms_exp_var_len_quote2(s, len, type);
	if (0 != *len)
		return (0);
	ms_exp_var_len_esc(s, len, type);
	if (0 != *len)
		return (0);
	ms_exp_var_len_none(s, len, type);
	if (0 != *len)
		return (0);
	return (0);
}
