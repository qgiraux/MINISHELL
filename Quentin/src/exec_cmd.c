/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 13:12:39 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_utils.h"
#include "../includes/redir.h"

int	ms_exec_expand(t_dlist *token)
{
	while (token)
	{
		if (MS_TOKEN_WORD == token->type)
		{
			;
		}
		token = token->next;
	}
	return (0);
}

int	ms_exec_locate(void)//char **av, char **env)
{
	return (0);
}

int	ms_exec_av(char **av, char **env, void *data)
{
	int		builtin_id;

	if (NULL != ft_strchr(av[0], MS_EXEC_BACKSLASH))
		return (ms_exec_locate());//av, env)); //
	builtin_id = ms_exec_builtin_id(av[0]);
	if (MS_N_BUILTIN != builtin_id)
		return (ms_exec_builtin(builtin_id, av, env, data)); //
	return (ms_exec_bin(av, env, data));
}

int	ms_exec_cmd(t_dlist *cmd, void *data)
{
	char	**env;
	char	**av;
	int		errnum;

	ms_redir_data_ini(&data);
	env = ms_exec_env(data);
	if (NULL == cmd)
		return (1);
	//printf("%s:%d\n", __FILE__, __LINE__);
	if (ms_redir_save(&cmd, data))
		return (1); //
	// if (-1 == ms_redir_dup2(data))
	// 	return (1); //
	if (ms_exec_expand(cmd))
		return (1); //
	av = ms_exec_dlist_to_av(cmd);
	if (NULL == av)
		return (1); //
	//ms_exec_redir(redir);
	//free redir
	//printf("%s:%d:%p\n", __FILE__, __LINE__, redir_out);
	// if (ms_exec_redir(&redir_in, &redir_out))
	// 	return (1); //
	//return (0);
	errnum = ms_exec_av(av, env, data);
	ms_redir_data_destroy(&data);
	return (errnum);
}
