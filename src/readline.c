/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:24:08 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:31:22 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <unistd.h>
#include "error.h"
#include "data.h"
#include "sig.h"
#include <stdio.h>
#include <termios.h>

#define MS_PROMPT "minishell> "
#define MS_ANSI_QUERY_POS "\033[6n"
#define MS_BAD_POS_MSG "\e[7m%\033[0m\n"
#define MS_ANSI_POS_START ';'
#define MS_ANSI_POS_END 'R'

static int	_hook(void)
{
	return (0);
}

static void	_newline(int sig)
{
	if (SIGINT == sig)
	{
		g_signum = SIGINT;
		rl_done = 1;
	}
}

static int	_ansi_pos(void)
{
	char			buff[30];
	size_t			i;
	struct termios	term;
	struct termios	restore;

	if (MS_DEBUG_DISABLE_TTYCHECK)
		return (1);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_putstr_fd(MS_ANSI_QUERY_POS, STDOUT_FILENO);
	i = 0;
	while (i < 30 && (1 == read(STDIN_FILENO, buff + i, 1)) \
			&& MS_ANSI_POS_END != buff[i])
		i++;
	if (2 > i || 30 == i || MS_ANSI_POS_END != buff[i])
		return (tcsetattr(STDIN_FILENO, TCSANOW, &restore), 1);
	while (i > 0 && buff[i] != MS_ANSI_POS_START)
		i--;
	tcsetattr(STDIN_FILENO, TCSANOW, &restore);
	return (tcsetattr(STDIN_FILENO, TCSANOW, &restore), ft_atoi(buff + i + 1));
}

/* ms_readline_clear:
 * Free readline buffers (cannot free all reachables)
 */
void	ms_readline_clear(void)
{
	if (rl_line_buffer)
		free(rl_line_buffer);
	rl_line_buffer = NULL;
	if (rl_prompt)
		free(rl_prompt);
	rl_prompt = NULL;
	if (rl_executing_macro)
		free(rl_executing_macro);
	rl_executing_macro = NULL;
	if (rl_executing_keyseq)
		free(rl_executing_keyseq);
	rl_executing_keyseq = NULL;
	rl_clear_history();
}

/* ms_readline:
 * Read line
 * Newline on ctrl-c, Nothing on ctrl-\, Quits on ctr-d
 * Adds lines in history (excluded "")
 */
int	ms_readline(char **line, void *data)
{
	int		pos;

	g_signum = 0;
	rl_event_hook = &_hook;
	ms_sig_quit_ignore(0);
	ms_sig_int_act(&_newline, 0);
	pos = _ansi_pos();
	if (1 != pos)
		ft_putstr_fd(MS_BAD_POS_MSG, STDOUT_FILENO);
	*line = readline(MS_PROMPT);
	if (SIGINT == g_signum)
	{
		ms_data_exit_pipe_set(MS_EXIT_FATAL_SIG + g_signum, data);
		return (MS_SUCCESS);
	}
	else if (SIGINT != g_signum && NULL == *line)
		ms_data_exit_shell_set(1, data);
	else
	{
		if (0 == g_signum && '\0' != *line[0])
			add_history(*line);
	}
	return (MS_SUCCESS);
}
