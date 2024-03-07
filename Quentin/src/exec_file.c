/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/06 14:09:13 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "exec_utils.h"
#include "env.h"


int	ms_exec_file(char *path, char **av, char **env, void *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (-1 == pid)
		return (errno); //
	if (0 == pid)
	{
		if (-1 == ms_redir_dup2(data))
			exit(1); //
		if (-1 == execve(path, av, env))
			exit(errno);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	return (0);
}
