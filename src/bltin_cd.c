/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/26 14:25:52 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"
#include "error.h"
#include "bltin.h"
#include "fprintf.h"

static char	*ms_is_in_env(char *variable, void *data)
{
	int		len;
	char	**env;
	int		i;

	i = 0;
	len = ft_strlen(variable);
	env = ms_data_env_get(data);
	while (NULL != env[i])
	{
		if (0 == ft_strncmp(variable, env[i], len) && '=' == env[i][len])
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	_err_msg(char *str, int errnum)
{
	t_csd		args;
	const char	*s[3] = {str, strerror(errnum), NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(2, "ms: cd: `%s': %s\n", &args);
}

static int	ms_set_old_pwd(void *data)
{
	char	*av[3];

	if (NULL == ms_is_in_env("PWD", data))
	{
		av[0] = "unset";
		av[1] = "OLDPWD";
		av[2] = NULL;
		if (MS_SUCCESS != ms_bltin_unset(av, data))
			return (1);
		return (0);
	}
	else
	{
		av[0] = "export";
		av[1] = ft_strjoin("OLDPWD=", ms_is_in_env("PWD", data));
		if (NULL == av[1])
			return (1);
		av[2] = NULL;
		if (MS_SUCCESS != ms_bltin_export(av, data))
			return (free(av[1]), 1);
		return (free(av[1]), 0);
	}
}

static int	ms_set_new_pwd(void *data, char *cwd)
{
	char	*av[3];

	if (NULL == ms_is_in_env("PWD", data))
		return (0);
	av[0] = "export";
	av[1] = ft_strjoin("PWD=", cwd);
	if (NULL == av[1])
		return (1);
	av[2] = 0;
	if (MS_SUCCESS != ms_bltin_export(av, data))
		return (free(av[1]), 1);
	return (free(av[1]), 0);
}

int	ms_bltin_cd(char **av, void *data)
{
	char	*cwd;

	if (NULL == av[0])
		return (1);
	else if (NULL != av[1] && NULL != av[2])
		return (ft_putstr_fd("cd: too many arguments\n" \
	, STDERR_FILENO), MS_EXIT_BLTIN_BAD_ARG);
	else if (NULL == av[1])
	{
		if (NULL == getenv("HOME"))
			return (ft_putstr_fd("HOME not set\n", STDERR_FILENO), 0);
		cwd = getenv("HOME");
		if (NULL == cwd)
			return (1);
		chdir(cwd);
	}
	else if (MS_SUCCESS != chdir(av[1]))
		return (_err_msg(av[1], errno), errno = 0, 1);
	cwd = getcwd(NULL, 0);
	if (NULL == cwd)
		return (1);
	if (1 == ms_set_old_pwd(data) || 1 == ms_set_new_pwd(data, cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}
