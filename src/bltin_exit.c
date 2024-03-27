/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/26 16:28:24 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"
#include "fprintf.h"

static int	ms_bltin_exit_code(char *code, int *res)
{
	int			n;
	int			neg;

	if ('\0' == *code)
		return (-1);
	n = 0;
	neg = 1;
	while ((code[n] >= 9 && code[n] <= 13) || code[n] == 32)
		n++;
	if (code[n] == '+' || code[n] == '-')
	{
		if (code[n++] == '-')
			neg = -neg;
	}
	while (code[n] >= '0' && code[n] <= '9')
		*res = *res * 10 + code[n++] - 48;
	while ((code[n] >= 9 && code[n] <= 13) || code[n] == 32)
		n++;
	if (0 != code[n])
		return (-1);
	return (1);
}

static void	_err_msg(char *str1)
{
	t_csd		args;
	const char	*s[2] = {str1, NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(2, "ms: exit: %s: numeric argument required\n", &args);
}

int	ms_bltin_exit(char **av, void *data)
{
	int	exit_code;

	exit_code = 0;
	if (NULL == av[0])
		return (1);
	if (NULL == av[1])
		return (ms_data_exit_shell_set(0, data), 0);
	if (NULL != av[1] && -1 == ms_bltin_exit_code(av[1], &exit_code))
	{
		_err_msg(av[1]);
		ms_data_exit_shell_set(MS_EXIT_BLTIN_BAD_ARG, data);
		return (MS_EXIT_BLTIN_BAD_ARG);
	}
	if (NULL != av[2])
	{
		ft_putstr_fd("ms: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	ms_data_exit_shell_set((exit_code % 256), data);
	return (exit_code % 256);
}
