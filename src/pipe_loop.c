/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:23:48 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/22 15:10:00 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	is_in_file(char **argv, t_fct f, int in)
{
	if (in == -1)
	{
		perror (argv[1]);
		pipe(f.pipefd[0]);
		close(f.pipefd[0][1]);
		return (0);
	}
	return (-1);
}

int	pipe_loop_bonus(t_fct f, int argc, char **argv)
{
	int		in;
	int		i;

	in = open(argv[1], O_RDONLY);
	i = is_in_file(argv, f, in);
	while (++i < argc - 3)
	{
		f.status[i] = 0;
		pipe(f.pipefd[i]);
		f.pid[i] = fork();
		if (f.pid[i] == -1)
			f.status[i] = 28;
		if (f.pid[i] == 0)
			f.status[i] = for_child(f, i, in);
		close (f.pipefd[i][1]);
	}
	i = 0;
	while (++i < argc - 3)
		waitpid (f.pid[i], &f.status[i], 0);
	return (WEXITSTATUS(f.status[argc - 4]));
}

int	for_child(t_fct f, int i, int in)
{
	int	out;

	if (i == f.argc - 4)
	{
		if (f.cat == 0)
			out = open(f.argv[f.argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			out = open(f.argv[f.argc - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (open(f.argv[f.argc - 1], O_WRONLY) < 0)
			return (perror(f.argv[f.argc - 1]), errno);
		dup2 (out, 1);
	}
	if (i > 0)
	{
		close (f.pipefd[i - 1][1]);
		dup2 (f.pipefd[i - 1][0], 0);
	}
	if (i < f.argc - 4)
	{
		close (f.pipefd[i][0]);
		dup2 (f.pipefd[i][1], 1);
	}
	if (i == 0)
		dup2 (in, 0);
	return (did_child_work(f, i, in));
}

int	did_child_work(t_fct f, int i, int in)
{
	if (in == -1 && i == 0)
	{
		free_all (f);
		exit (errno);
	}
	f.fct[i] = check_paths(f.function[i][0], f.env, -1);
	if (f.fct[i] == NULL)
	{
		write (2, f.function[i][0], ft_strlen(f.function[i][0]));
		write (2, ": command not found\n", 20);
		free_all (f);
		exit (127);
	}
	f.status[i] = execve(f.fct[i], f.function[i], NULL);
	perror (f.function[i][0]);
	free_all(f);
	exit (errno);
}
