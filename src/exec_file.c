/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/27 13:04:23 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "exec_utils.h"
#include "env.h"
#include "error.h"
#include "sig.h"
#include "data.h"
#include <readline/readline.h>
#include "fprintf.h"

static int	_parent_sig(int status)
{
	g_signum = WTERMSIG(status);
	if (SIGINT == g_signum)
		ft_putstr_fd(MS_EXEC_INTMSG, STDOUT_FILENO);
	else if (SIGQUIT == g_signum)
		ft_putstr_fd(MS_EXEC_QUITMSG, STDOUT_FILENO);
	else if (SIGPIPE == g_signum)
		;
	else
		return (ms_e(__FILE__, __LINE__, 1), 1);
	return (MS_EXIT_FATAL_SIG + g_signum);
}

static int	_parent_wait(pid_t pid)
{
	pid_t	rpid;
	int		status;

	rpid = waitpid(pid, &status, 0);
	if (0 == rpid)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	else if (-1 == rpid)
		return (ms_perror(MS_E), 1);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (_parent_sig(status));
	else
		return (ms_e(__FILE__, __LINE__, 1), 1);
	return (MS_SUCCESS);
}

static void	_error(char *path, int errnum)
{
	t_csd		args;
	const char	*s[4] = {MS_E, path, strerror(errnum), NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(STDERR_FILENO, "%s: %s: %s\n", &args);
}

static void	_exit_child(int exit_code, char *path, char **av, void *data)
{
	ms_data_destroy_main(data);
	free(path);
	ms_exec_free_av(av);
	exit(exit_code);
}

int	ms_exec_file(char *path, char **av, char **env, void *data)
{
	pid_t	pid;

	pid = fork();
	ms_sig_ignore(SIGQUIT, 1);
	ms_sig_ignore(SIGINT, 1);
	if (-1 == pid)
		return (ms_perror(MS_E), 1);
	if (0 == pid)
	{
		ms_sig_handle(NULL, 0);
		if (-1 == ms_redir_dup2(data))
			_exit_child(errno, path, av, data);
		if (-1 == execve(path, av, env))
		{
			_error(path, errno);
			_exit_child(MS_EXIT_NOT_EXE, path, av, data);
		}
		_exit_child(1, path, av, data);
	}
	return (_parent_wait(pid));
}
