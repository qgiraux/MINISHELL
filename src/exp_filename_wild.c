/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_wild.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/29 14:36:18 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token.h"
#include "exp_utils.h"

static void	_match(char *name, char *ptrn, size_t *i_n, size_t i_p)
{
	while (name[*i_n] && name[*i_n] != ptrn[i_p])
		(*i_n)++;
}

static void	_skip_rep(char *ptrn, size_t *i_p)
{
	while (EXP_WILD == ptrn[*i_p] && EXP_WILD == ptrn[*i_p + 1])
		(*i_p)++;
}

static int	_pos_offset(char *ptrn, size_t i_p)
{
	size_t	pos;
	char	quote;
	char	c;

	pos = 0;
	quote = '\0';
	c = ptrn[i_p + pos];
	while ('\0' != c)
	{
		if (EXP_ESC == c)
			return (pos + 1);
		if ('\0' != quote && c == quote)
			quote = '\0';
		else if ((MS_QUOTE_1 == c || MS_QUOTE_2 == c))
			quote = c;
		else
			return (pos);
		c = ptrn[i_p + ++pos];
	}
	return (pos);
}

int	exp_filename_wild(char *name, char *ptrn, size_t *i_n, size_t *i_p)
{
	size_t	off;

	_skip_rep(ptrn, i_p);
	if (EXP_WILD == ptrn[*i_p])
	{
		if ('\0' == ptrn[*i_p + 1])
			return (*i_n = ft_strlen(name), *i_p = ft_strlen(ptrn), 0);
		else
		{
			(*i_p)++;
			off = _pos_offset(ptrn, *i_p);
			if ('\0' == ptrn[*i_p + off])
				return (*i_n = ft_strlen(name), *i_p = ft_strlen(ptrn), 0);
			else if (EXP_WILD == ptrn[*i_p + off])
				return (*i_p += off, 0);
			_match(name, ptrn, i_n, *i_p + off);
			if ('\0' == name[(*i_n)])
				return (1);
		}
	}
	return (0);
}
