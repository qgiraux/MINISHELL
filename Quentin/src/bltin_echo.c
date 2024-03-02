/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:35:33 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bltin_utils.h"

int	ms_bltin_echo(char **av, char **env, void *data)
{
	int	i;
	int	f_out;
	int	opt_n;

	(void)env;
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
