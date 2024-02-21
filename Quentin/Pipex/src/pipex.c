/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:21 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/19 14:28:41 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_fct		f;
	t_mainvar	m;
	int			status;

	if (argc == 1)
		return (0);
	m = init_mainvar(argc, argv, env);
	m = is_it_here(m);
	if (m.argc < 5)
		return (0);
	f = init_bonus(m.argv, m.argc, m.env);
	f.cat = m.cat;
	status = pipe_loop_bonus(f, m.argc, m.argv);
	free_all(f);
	unlink("here_doc");
	return (status);
}

t_fct	init_bonus(char **argv, int argc, char **env)
{
	t_fct	f;
	int		i;

	f.argc = argc;
	f.function = malloc ((argc - 3) * sizeof (char **));
	f.fct = malloc ((argc - 3) * sizeof (char *));
	f.pid = malloc ((argc - 3) * sizeof (int));
	f.pipefd = malloc ((argc - 3) * sizeof (int *));
	f.status = malloc ((argc - 3) * sizeof (int));
	f.argv = argv;
	f.env = env;
	i = 0;
	while (i < argc - 3)
	{
		f.function[i] = ft_split(argv[i + 2], ' ');
		f.pipefd[i] = malloc (2 * sizeof(int));
		f.status[i] = 0;
		i++;
	}
	return (f);
}

void	free_all(t_fct f)
{
	int	i;
	int	j;

	i = -1;
	while (++i < f.argc - 3)
	{
		j = -1;
		while (f.function[i][++j])
			free (f.function[i][j]);
		free(f.function[i]);
		free(f.pipefd[i]);
	}
	free(f.function);
	free (f.fct);
	free (f.pipefd);
	free (f.pid);
	free (f.status);
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free (str);
}

t_mainvar	init_mainvar(int argc, char **argv, char **env)
{
	t_mainvar	m;

	m.argc = argc;
	m.argv = argv;
	m.env = env;
	return (m);
}
