/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/26 14:25:55 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "bltin_export_utils.h"
#include "env.h"
#include "data.h"
#include "error.h"
#include "exec_utils.h"
#include "fprintf.h"

static int	ms_data_env_export_line(char *new_line, void *data)
{
	char	*variable;
	char	**env;

	env = ms_data_env_get(data);
	variable = ms_mget_variable(new_line);
	if (NULL == ms_env_get_line((const char **)env, variable))
		return (ms_data_env_add_line(data, env, variable, new_line));
	else
		return (ms_data_env_replace_line(env, variable, new_line));
}

static void	_err_msg(char *str)
{
	t_csd		args;
	const char	*s[2] = {str, NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(2, "ms: export: `%s': not a valid identifier\n", &args);
}

int	ms_bltin_export(char **av, void *data)
{
	int		arg_n;

	arg_n = 1;
	while (NULL != av[arg_n])
	{
		if (NULL == ft_strchr(av[arg_n], '=') \
		|| MS_SUCCESS != ms_is_variable(av[arg_n]))
		{
			_err_msg(av[arg_n]);
			return (1);
		}
		else
			if (1 == ms_data_env_export_line(av[arg_n], data))
				return (1);
		arg_n++;
	}
	return (0);
}
