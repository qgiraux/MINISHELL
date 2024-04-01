/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_wild_match.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/04/01 16:16:30 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token.h"
#include "exp_utils.h"

static int	_str_match(char *name, char *ptrn, size_t *offset_name_pattern)
{
	size_t	i_n;
	size_t	i_p;

	i_n = 0;
	i_p = 0;
	if (exp_filename_str_match(name, ptrn, &i_n, &i_p))
	{
		offset_name_pattern[0] += i_n;
		offset_name_pattern[1] += i_p;
		return (1);
	}
	return (0);
}

static int	_match(\
	char **name, char *ptrn, int *values_quote_esc, size_t *offset_name_pattern)
{
	if ('\0' == *ptrn)
		return (offset_name_pattern[0] += ft_strlen(*name), 1);
	while (**name)
	{
		if (values_quote_esc[0])
			ptrn++;
		while (**name && **name != *ptrn && ++(offset_name_pattern[0]))
			(*name)++;
		if ('\0' == **name)
			return (0);
		if (values_quote_esc[0])
			ptrn--;
		if (_str_match(*name, ptrn, offset_name_pattern))
			return (1);
		++(offset_name_pattern[0]);
		(*name)++;
	}
	return (0);
}

static void	_skip_to_valid_char(\
	char **ptrn, int *values_quote_esc, size_t	*offset_name_pattern)
{
	while ('\0' != **ptrn)
	{
		if (EXP_ESC == **ptrn && ++(*ptrn) && ++(offset_name_pattern[0]))
			return ;
		if (**ptrn == values_quote_esc[0])
			values_quote_esc[0] = '\0';
		else if ((MS_QUOTE_1 == **ptrn || MS_QUOTE_2 == **ptrn))
			values_quote_esc[0] = **ptrn;
		else if (values_quote_esc[0] && --(offset_name_pattern[1]) && --(*ptrn))
			return ;
		else
			return ;
		(*ptrn)++;
		(offset_name_pattern[1])++;
	}
	return ;
}

static void	_skip_rep(\
	char *ptrn, size_t *i_p, int *values_quote_esc, size_t *offset_name_pattern)
{
	offset_name_pattern[0] = 0;
	offset_name_pattern[1] = 0;
	values_quote_esc[0] = 0;
	values_quote_esc[1] = 0;
	while (EXP_WILD == ptrn[*i_p] && EXP_WILD == ptrn[*i_p + 1])
		(*i_p)++;
	if (EXP_WILD == ptrn[*i_p] || '\0' == ptrn[*i_p])
		return ;
	ptrn += *i_p;
	_skip_to_valid_char(&ptrn, values_quote_esc, offset_name_pattern);
	(*i_p) += offset_name_pattern[1];
	offset_name_pattern[0] = 0;
	offset_name_pattern[1] = 0;
	values_quote_esc[0] = 0;
	values_quote_esc[1] = 0;
	return ;
}

int	exp_filename_wild_match(char *name, char *ptrn, size_t *i_n, size_t *i_p)
{
	int				values_quote_esc[2];
	size_t			o[2];

	_skip_rep(ptrn, i_p, values_quote_esc, o);
	name += *i_n;
	ptrn += *i_p;
	if (EXP_WILD != *ptrn)
	{
		if (_str_match(name, ptrn, o))
			return (*i_n += o[0], *i_p += o[1], 1);
		return (0);
	}
	if ('\0' == *(ptrn + 1))
		return (*i_n += o[0] + ft_strlen(name), *i_p += o[1] + 1, 1);
	if (EXP_WILD == *ptrn && ++(o[1]))
		ptrn++;
	_skip_to_valid_char(&ptrn, values_quote_esc, o);
	if (EXP_WILD == *ptrn || _match(&name, ptrn, values_quote_esc, o))
		return (*i_n += o[0], *i_p += o[1], 1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	size_t	i_n;
// 	size_t	i_p;

// 	if (3 > ac)
// 		return (1);
// 	if (3 < ac)
// 		i_n = ft_atoi(av[3]);
// 	else
// 		i_n = 0;
// 	if (4 < ac)
// 		i_p = ft_atoi(av[4]);
// 	else
// 		i_p = 0;
// 	printf("name=%s pattern=%s\n", av[1], av[2]);
// 	if (exp_filename_wild_match(av[1], av[2], &i_n, &i_p))
// 		printf("Match i_n=%zu(%c) i_p=%zu(%c)\n", i_n, av[1][i_n], i_p, av[2][i_p]);
// 	else
// 		printf("No match! i_n=%zu i_p=%zu\n", i_n, i_p);
// }
