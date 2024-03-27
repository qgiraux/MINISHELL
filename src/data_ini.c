/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 13:33:09 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "data.h"
#include "sig.h"

int	ms_data_ini_main(char **env, void *data, int (*f)(void *))
{
	const char	*data_token[10] = {\
		MS_CONTROL_PIPE,
		MS_CONTROL_AND, \
		MS_CONTROL_OR, \
		MS_CONTROL_OPEN, \
		MS_CONTROL_CLOSE, \
		MS_REDIR_INPUT, \
		MS_REDIR_OUTPUT, \
		MS_REDIR_APPEND, \
		MS_REDIR_HERE_DOC, \
		NULL};

	ms_data_exit_shell_ini(data);
	ms_data_exit_pipe_ini(data);
	ms_data_env_ini(data);
	if (ms_data_env_mset(env, data))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	ms_data_operator_set((char **)data_token, data);
	ms_data_ini_line(data);
	ms_data_ini_cmd(data);
	return (f(data));
}

int	ms_data_ini_line(void *data)
{
	ms_data_list_ini(data);
	return (MS_SUCCESS);
}

int	ms_data_ini_cmd(void *data)
{
	ms_data_files_ini(data);
	ms_data_redir_ini(data);
	return (MS_SUCCESS);
}
