/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/26 11:18:37 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"

int	_opt_n(char *s)
{
	if (NULL == s)
		return (0);
	if ('-' != s[0])
		return (0);
	if ('n' != *(++s))
		return (0);
	while ('n' == *s)
		s++;
	return ('\0' == *s);
}

int	ms_bltin_echo(char **av, void *data)
{
	int		i;
	int		f_out;
	int		opt_n;

	if (NULL == av || NULL == av[0])
		return (MS_EXIT_BLTIN_BAD_ARG);
	ms_data_redir_get(NULL, &f_out, data);
	i = 1;
	opt_n = _opt_n(av[1]);
	if (opt_n)
		i++;
	while (av[i])
	{
		write(f_out, av[i], ft_strlen(av[i]));
		if (av[++i])
			write(f_out, BLTIN_SEP, ft_strlen(BLTIN_SEP));
	}
	if (0 == opt_n)
		write(f_out, BLTIN_NEWLINE, 1);
	return (MS_SUCCESS);
}
