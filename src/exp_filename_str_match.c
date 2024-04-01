/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_str_match.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/04/01 15:22:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token.h"
#include "exp_utils.h"

static void	_ini_to_0(int *i2, size_t *s2)
{
	i2[0] = 0;
	i2[1] = 0;
	s2[0] = 0;
	s2[1] = 0;
}

static int	_update(char **name, char **ptrn, int *qe, size_t *off_np)
{
	if (qe[1])
	{
		qe[1] = 0;
		if (**ptrn == **name && ++(off_np[0]))
			(*name)++;
	}
	else
	{
		if (EXP_ESC == **ptrn)
			qe[1] = 1;
		else if (qe[0] && qe[0] == **ptrn)
			qe[0] = 0;
		else if (MS_QUOTE_1 == **ptrn || MS_QUOTE_2 == **ptrn)
			qe[0] = **ptrn;
		else if ('\0' == **name)
			*name = NULL;
		else if (**ptrn == **name && ++(off_np[0]))
			(*name)++;
		else
			return (0);
	}
	return (1);
}

int	exp_filename_str_match(char *name, char *ptrn, size_t *i_n, size_t *i_p)
{
	int		values_quote_esc[2];
	size_t	offset_name_pattern[2];

	name += *i_n;
	ptrn += *i_p;
	_ini_to_0(values_quote_esc, offset_name_pattern);
	while (name && *ptrn \
		&& (EXP_WILD != *ptrn || (values_quote_esc[0] || values_quote_esc[1])))
	{
		if (0 == _update(&name, &ptrn, values_quote_esc, offset_name_pattern))
			return (0);
		offset_name_pattern[1]++;
		ptrn++;
	}
	if (NULL == name)
		return (0);
	if (values_quote_esc[0])
		ptrn++;
	if (('\0' == *ptrn && '\0' == *name) || EXP_WILD == *ptrn)
	{
		(*i_n) += offset_name_pattern[0];
		(*i_p) += offset_name_pattern[1];
		return (1);
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	size_t	i_n;
// 	size_t	i_p;

// 	if (3 > ac)
// 		return (1);
// 	printf("name=%s\tpattern=%s\n", av[1], av[2]);
// 	if (3 < ac)
// 		i_n = ft_atoi(av[3]);
// 	else
// 		i_n = 0;
// 	if (4 < ac)
// 		i_p = ft_atoi(av[4]);
// 	else
// 		i_p = 0;
// 	if (exp_filename_str_match(av[1], av[2], &i_n, &i_p))
// 		printf("Match i_n=%zu(%c) i_p=%zu(%c)\n", i_n, av[1][i_n], i_p, av[2][i_p]);
// 	else
// 		printf("No match! i_n=%zu i_p=%zu\n", i_n, i_p);
// }
