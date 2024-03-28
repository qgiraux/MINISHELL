/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_escape.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/28 17:47:41 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"
#include "token.h"

static char	*_escape(char *s)
{
	char	*esc;
	char	*quote1;
	size_t	len;

	esc = ms_exp_escape(s, EXP_ESC_LIST);
	if (NULL == esc)
		return (ms_e(__FILE__, __LINE__, 0), NULL);
	len = ft_strlen(esc);
	quote1 = (char *)malloc(sizeof(char) * (len + 2 + 1));
	if (NULL == quote1)
		return (free(esc), ms_perror(MS_E), NULL);
	ft_memcpy(quote1 + 1, esc, len);
	free(esc);
	quote1[0] = MS_QUOTE_1;
	quote1[len + 1] = MS_QUOTE_1;
	quote1[len + 2] = '\0';
	return (quote1);
}

char	*exp_parameter_escape(char *big, size_t len_str, int type)
{
	char	*str;

	if (MS_PARA_QUOTE1 == type)
		str = (char *)malloc(sizeof(char) * (len_str - 2 + 1));
	else
		str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (NULL == str)
		return (ms_perror(MS_E), NULL);
	if (MS_PARA_QUOTE1 == type)
		ft_strlcpy(str, big + 1, len_str - 2 + 1);
	else
		ft_strlcpy(str, big, len_str + 1);
	if (MS_PARA_ESC_ME == type)
		return (_escape(str));
	else if (MS_PARA_QUOTE1 == type)
		return (_escape(str));
	return (str);
}

// static int	_list_madd(t_dlist **values, char *big, size_t len_str, int type)
