/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:29:21 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "redir.h"
#include "exp.h"
#include "env.h"

static int	ms_exec_cmd_builtin(char **av, void *data, int has_slash)
{
	int		builtin_id;

	if (!has_slash)
	{
		builtin_id = ms_exec_builtin_id(av[0]);
		if (MS_N_BUILTIN != builtin_id)
			return (ms_exec_builtin(builtin_id, av, data)); // TODO
	}
	return (-1);
}

static int	ms_exec_cmd_efile(char **av, char **env, void *data, int has_slash)
{
	int		return_code;
	char	*file_path;

	if (has_slash)
	{
		file_path = ft_strdup(av[0]);
		if (NULL == file_path)
			return (ms_perror(MS_E), 1);
	}
	else
	{
		if (ms_exec_bin_mget_path(&file_path, av[0], (const char **)env))
			return (ms_e(__FILE__, __LINE__, 0), 1);
	}
	if (NULL != file_path)
	{
		return_code = ms_exec_file(file_path, av, env, data);
		return (free(file_path), return_code);
	}
	return (-1);
}

static int	ms_exec_cmd_av(char **av, void *data)
{
	char	**env;
	int		return_code;
	int		has_slash;

	env = ms_env(data);
	has_slash = (NULL != ft_strchr(av[0], PATH_SEP));
	return_code = ms_exec_cmd_builtin(av, data, has_slash);
	if (-1 != return_code)
		return (return_code);
	return_code = ms_exec_cmd_efile(av, env, data, has_slash);
	if (-1 != return_code)
		return (return_code);
	return (ms_exec_error(av[0], EEXEC_NOCMD), 1);
}

/* ms_exec_cmd:
 * Exec command from <cmd> list
 * Redir info is temporarily malloc'ed in data
 */

int	ms_exec_cmd(t_dlist *cmd, void *data)
{
	char	**av;
	int		errnum;

	if (NULL == cmd)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	ms_redir_data_ini(&data);
	if (ms_redir_save(&cmd, data))
		return (ms_redir_data_destroy(&data), 1);
	if (ms_exp(&cmd, data))
		return (ms_redir_data_destroy(&data), 1);
	av = ms_exec_dlist_to_av(cmd);
	if (NULL == av)
		return (ms_redir_data_destroy(&data), 1);
	errnum = ms_exec_cmd_av(av, data);
	ms_redir_data_destroy(&data);
	return (errnum);
}
