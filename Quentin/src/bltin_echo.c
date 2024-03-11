/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/11 11:50:14 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"

int	ms_bltin_echo(char **av, void *data)
{
	int		i;
	int		f_out;
	int		opt_n;

	i = 1;
	if (NULL == av[i])
		return (0);
	ms_redir_data_get(NULL, &f_out, data);
	opt_n = (0 == ft_strncmp(av[i], BLTIN_OPTN, 1 + sizeof(BLTIN_OPTN)));
	if (opt_n)
		i++;
	while (av[i])
	{
		write(f_out, av[i], ft_strlen(av[i]));
		if (av[++i])
			write(f_out, BLTIN_SEP, sizeof(BLTIN_SEP));
	}
	if (0 == opt_n)
		write(f_out, BLTIN_NEWLINE, 1);
	return (0);
}
