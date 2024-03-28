/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/28 10:24:23 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "redir.h"
#include "exp.h"
#include "env.h"
#include "data.h"
#include "fprintf.h"

static void	_error(char *cmd)
{
	const int	fd_error = 2;
	t_csd		args;
	const char	*s[2] = {cmd, NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(fd_error, EEXEC_NOCMD_MSG, &args);
}

static int	_exec_builtin(char **av, void *data, int has_slash)
{
	int		builtin_id;

	if (!has_slash)
	{
		builtin_id = ms_exec_builtin_id(av[0]);
		if (MS_N_BUILTIN != builtin_id)
			return (ms_exec_builtin(builtin_id, av, data));
	}
	return (-1);
}

static int	_exec_efile(char **av, char **env, void *data, int has_slash)
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

static int	_exec_av(char **av, void *data)
{
	char	**env;
	int		return_code;
	int		has_slash;

	env = ms_data_env_get(data);
	has_slash = (NULL != ft_strchr(av[0], PATH_SEP));
	return_code = _exec_builtin(av, data, has_slash);
	if (-1 != return_code)
		return (return_code);
	return_code = _exec_efile(av, env, data, has_slash);
	if (-1 != return_code)
		return (return_code);
	return (_error(av[0]), MS_EXIT_NOT_FOUND);
}

/* ms_exec_cmd:
 * Exec command from <cmd> list
 * Redir info is temporarily malloc'ed in data
 */
int	ms_exec_cmd(t_dlist **ptr_list, void *data)
{
	char	**av;
	int		exit_code;
	t_dlist	*cmd;

	if (NULL == *ptr_list || NULL == data)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	cmd = *ptr_list;
	*ptr_list = NULL;
	ms_data_ini_cmd(data);
	if (ms_redir_save(&cmd, data))
		return (ms_data_destroy_cmd(data), ms_dlstclear(&cmd), 1);
	if (ms_exp(&cmd, data))
		return (ms_data_destroy_cmd(data), ms_dlstclear(&cmd), 1);
	if (ms_exec_dlist_to_av(&cmd, &av))
		return (ms_data_destroy_cmd(data), 1);
	if (NULL == av)
		return (MS_SUCCESS);
	exit_code = _exec_av(av, data);
	ms_exec_free_av(av);
	ms_data_exit_pipe_set(exit_code, data);
	ms_data_destroy_cmd(data);
	return (exit_code);
}
