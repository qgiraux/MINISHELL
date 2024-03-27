/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 12:56:27 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"
#include "error.h"
#include "exec_utils.h"

static int	ms_is_unset_in_env(char *variable, void *data)
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
			return (0);
		i++;
	}
	return (11);
}

static void	free_all_variables(char **env, char *variable, int i)
{
	while (NULL != env[++i])
		free (env[i]);
	free(env);
	free(variable);
}

static int	ms_data_env_remove_line(void *data \
, char **env, char *variable, char **new_env)
{
	int		i;
	int		j;

	j = 0;
	while (NULL != env[j])
		j++;
	new_env = malloc(j * sizeof(char *));
	if (NULL == new_env)
		return (free (variable), ms_perror(MS_E), 1);
	i = --j;
	new_env[i] = NULL;
	while (--i >= 0)
	{
		if (0 == ft_strncmp(variable, env[j], (ft_strlen(variable))) \
		&& '=' == env[j][ft_strlen(variable)])
			j--;
		if (j >= 0)
			new_env[i] = ft_strdup(env[j]);
		if (NULL == new_env[i])
			return (free_all_variables(env, variable, i), ms_perror(MS_E), 1);
		j--;
	}
	return (ms_data_env_mset(new_env, data), ms_exec_free_av(new_env), 0);
}

int	ms_bltin_unset(char **av, void *data)
{
	int		arg_n;
	char	**env;

	arg_n = 1;
	while (NULL != av[arg_n])
	{
		if (NULL != ft_strchr(av[arg_n], '='))
			return (0);
		if (0 != ms_is_unset_in_env(av[arg_n], data))
			return (0);
		env = ms_data_env_get(data);
		if (1 == ms_data_env_remove_line(data, env, av[arg_n], NULL))
			return (1);
		arg_n++;
	}
	return (0);
}
