/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:00:24 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 13:58:42 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"
#include "exec_utils.h"
#include "error.h"

static int	debug_builtin(char **av, void *data)
{
	int	i;

	(void)data;
	ft_putstr_fd("debug_builtin:\n", 1);
	i = 0;
	while (av[i])
	{
		ft_putstr_fd(av[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
	return (0);
}

int	ms_exec_builtin_id(char *cmd_name)
{
	const char	*builtin_name[MS_N_BUILTIN + 1] = {\
		MS_BUILTIN_ECHO, MS_BUILTIN_CD, MS_BUILTIN_PWD, \
		MS_BUILTIN_EXPORT, MS_BUILTIN_UNSET, MS_BUILTIN_ENV, \
		MS_BUILTIN_EXIT, NULL};
	int			i;

	i = 0;
	while (builtin_name[i] && 0 != ft_strncmp(builtin_name[i], cmd_name, ft_strlen(cmd_name) + 1))
		i++;
	return (i);
}

int	ms_exec_builtin(int builtin_id, char **av, void *data)
{
	const t_builtin	builtin_fun[MS_N_BUILTIN + 1] = {\
		&ms_bltin_echo, &debug_builtin, &ms_bltin_pwd, \
		&debug_builtin, &debug_builtin, &debug_builtin, \
		&debug_builtin, NULL};
	t_builtin		f;

	f = builtin_fun[builtin_id];
	if (NULL == f)
		return (1); //
	f(av, data);
	return (0);
}

