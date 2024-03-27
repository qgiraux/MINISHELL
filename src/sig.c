/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:06:46 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/20 14:51:08 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "sig.h"
#include "libft.h"
#include "readline.h"
#include <termios.h>

volatile sig_atomic_t	g_signum;

/* ms_sig_int_act:
 * Changes CTRL-C behavior
 * if NULL == handler then default behavior
 * if NULL != handler then us handler
 * if restart then allows WIFSIGNALED
 */
int	ms_sig_int_act(void (*handler)(int), int restart)
{
	struct sigaction	act;

	if (NULL == handler)
		act.sa_handler = SIG_DFL;
	else
		act.sa_handler = handler;
	if (restart)
		act.sa_flags = SA_RESTART;
	else
		act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (-1 == sigaction(SIGINT, &act, NULL))
		return (ms_perror(MS_E), 1);
	return (MS_SUCCESS);
}

/* ms_sig_ignore:
 * Ignores a signal <signum> (SIGINT, SIGQUIT, etc)
 */
int	ms_sig_ignore(int signum, int restart)
{
	struct sigaction	act;

	(void)restart;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	if (-1 == sigaction(signum, &act, NULL))
		return (ms_perror(MS_E), 1);
	return (MS_SUCCESS);
}

/* ms_sig_quit_ignore:
 * Changes CTRL-/ behavior
 * if restart then allows WIFSIGNALED
 */
int	ms_sig_quit_ignore(int restart)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	if (restart)
		act.sa_flags = SA_RESTART;
	else
		act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (-1 == sigaction(SIGQUIT, &act, NULL))
		return (ms_perror(MS_E), 1);
	return (MS_SUCCESS);
}

/* ms_sig_int_act:
 * Changes CTRL-C and CTRL-/ behavior
 * if NULL == handler then default behavior
 * if NULL != handler then us handler
 * if restart then allows WIFSIGNALED
 */
int	ms_sig_handle(void (*handler)(int), int restart)
{
	struct sigaction	act;

	if (0 == restart && NULL == handler)
		act.sa_handler = SIG_DFL;
	else if (0 != restart && NULL == handler)
		act.sa_handler = SIG_IGN;
	else
		act.sa_handler = handler;
	if (restart && NULL != handler)
		act.sa_flags = SA_RESTART;
	else
		act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (-1 == sigaction(SIGINT, &act, NULL))
		return (ms_perror(MS_E), 1);
	if (-1 == sigaction(SIGQUIT, &act, NULL))
		return (ms_perror(MS_E), 1);
	return (MS_SUCCESS);
}
