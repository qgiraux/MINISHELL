/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:26:37 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"

static void	_len_name(char *s, size_t *len, int *type)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return ;
	i = 0;
	if (EXP_UNDERSCORE == s[0] || ft_isalpha(s[0]))
		i++;
	else
		return ;
	while (EXP_UNDERSCORE == s[i] || ft_isalnum(s[i]))
		i++;
	if (0 != i)
		*type = MS_PARA_NAME;
	*len = i + 1;
}

static void	_type_spe(char *s, size_t *len, int *type)
{
	if (EXP_SPE0 == *s)
	{
		*len = 2;
		*type = MS_PARA_SPE0;
	}
	else
		*type = MS_PARA_STR;
}

int	ms_parameter_var(char *s, size_t *len, int *type)
{
	if (NULL == s || '\0' == *s)
		return (1);
	*type = MS_PARA_STR;
	if (EXP_VAR != s[0])
		return (0);
	_len_name(s + 1, len, type);
	if (MS_PARA_STR != *type)
		return (0);
	_type_spe(s + 1, len, type);
	if (MS_PARA_STR != *type)
		return (0);
	*len = 1;
	*type = MS_PARA_STR;
	return (0);
}
