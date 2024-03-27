/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 14:57:53 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"

int	ms_bltin_env(char **av, void *data)
{
	char	**env;
	int		f_out;

	if (NULL == av[0])
		return (ft_putstr_fd("no parameters\n", STDERR_FILENO), 1);
	if (NULL != av[1])
	{
		ft_putstr_fd("env: Too many parmaters", STDERR_FILENO);
		ft_putstr_fd(BLTIN_NEWLINE, STDERR_FILENO);
	}
	ms_data_redir_get(NULL, &f_out, data);
	env = ms_data_env_get(data);
	if (NULL == env)
		return (1);
	while (NULL != *env)
	{
		ft_putstr_fd(*env, f_out);
		ft_putstr_fd(BLTIN_NEWLINE, f_out);
		env++;
	}	
	return (0);
}
