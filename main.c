/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:54:20 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/27 13:39:39 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "error.h"
#include "dlist.h"
#include "node.h"
#include "sig.h"
#include "readline.h"
#include "here.h"
#include <readline/readline.h>

int	_main_istty_err(void)
{
	if (MS_DEBUG_DISABLE_TTYCHECK)
		return (MS_SUCCESS);
	else if (0 == isatty(STDIN_FILENO))
		return (1);
	else if (0 == isatty(STDOUT_FILENO))
		return (1);
	return (MS_SUCCESS);
}

static int	_main_loop(void *data)
{
	t_dlist	*list;
	char	*input;

	while (MS_NOEXIT == ms_data_exit_shell_get(data))
	{
		errno = 0;
		ms_readline(&input, data);
		if (NULL != input && SIGINT != g_signum)
		{
			g_signum = 0;
			list = ms_interpreter(input, data);
			if (NULL == list)
				;
			else
			{
				ms_data_list_set(list, data);
				ms_node(list, 0, data);
			}
			ms_data_destroy_line(data);
			rl_done = 1;
		}
		if (NULL != input)
			free(input);
	}
	return (MS_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		return_code;

	(void)argc;
	(void)argv;
	if (_main_istty_err())
		return (1);
	ms_data_ini_main(envp, &data, &_main_loop);
	if (0 == MS_DEBUG_DISABLE_TTYCHECK)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	ms_here_rm_tmp();
	return_code = ms_data_exit_shell_get(&data);
	ms_data_destroy_main(&data);
	return (return_code);
}
