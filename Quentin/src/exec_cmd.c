/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:20:16 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "redir.h"
#include "env.h"
#include "exp.h"

int	ms_exec_locate(char **av, char **env)
{
	(void)av;
	(void)env;
	return (0);
}

int	ms_exec_av(char **av, char **env, void *data)
{
	int		builtin_id;
	int		has_slash;
	int		err;
	char	*file_path;

	//return (ms_exec_locate(av, env)); //
	has_slash = (NULL != ft_strchr(av[0], PATH_SEP));
	if (has_slash)
	{
		builtin_id =  ms_exec_builtin_id(av[0]);
		if (MS_N_BUILTIN != builtin_id)
			return (ms_exec_builtin(builtin_id, av, env, data)); //
	}
	if (has_slash)
		file_path = ft_strdup(av[0]);
	else
		file_path = ms_exec_bin_path(av[0], (const char **)env);
	if (NULL == file_path)
		return (1);
	err = ms_exec_file(file_path, av, env, data);
	if (err)
	{
		; //
	}
	return (free(file_path), err);
}

int	ms_exec_cmd(t_dlist *cmd, void *data)
{
	char	**env;
	char	**av;
	int		errnum;

	ms_redir_data_ini(&data);
	env = ms_env(data);
	if (NULL == cmd)
		return (1);
	if (ms_redir_save(&cmd, data))
		return (1); //
	if (ms_exp(&cmd, data))
		return (1); //
	av = ms_exec_dlist_to_av(cmd);
	if (NULL == av)
		return (1); //
	errnum = ms_exec_av(av, env, data);
	ms_redir_data_destroy(&data);
	return (errnum);
}