/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:37:48 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "exec_utils.h"
#include "env.h"
#include "error.h"

int	ms_exec_file(char *path, char **av, char **env, void *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (-1 == pid)
		return (ms_perror(MS_E), 1);
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
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status)); //SIGNAL MANAGEMENT
		else if (WIFSTOPPED(status))
			return (WSTOPSIG(status)); //SIGNAL MANAGEMENT
		else
			return (ms_e(__FILE__, __LINE__, 1), 1);
	}
	return (0);
}
