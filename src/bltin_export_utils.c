/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:06:37 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 11:13:26 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include "data.h"
#include "error.h"
#include "exec_utils.h"

int	ms_is_variable(char *s)
{
	size_t	i;

	if (NULL == s || '\0' == *s)
		return (1);
	i = 0;
	if (MS_UNDERSCORE == s[0] || ft_isalpha(s[0]))
		i++;
	else
		return (1);
	while (MS_UNDERSCORE == s[i] || ft_isalnum(s[i]))
		i++;
	if ('=' == s[i])
		return (MS_SUCCESS);
	return (1);
}

char	*ms_mget_variable(char *str)
{
	char	*variable;
	int		size;

	size = 0;
	while ('=' != str[size])
		size++;
	variable = malloc((size + 1) * sizeof(char));
	if (NULL == variable)
		return (ms_perror(MS_E), NULL);
	return (ft_strlcpy(variable, str, size + 1), variable);
}

int	ms_data_env_add_line(void *data \
, char **env, char *variable, char *new_line)
{
	int		i;
	char	**new_env;

	i = 0;
	while (NULL != env[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	new_env[i + 1] = NULL;
	new_env[i] = ft_strdup(new_line);
	if (NULL == new_env[i])
		return (free (variable), free (new_env), ms_perror(MS_E), 1);
	while (--i >= 0)
	{
		new_env[i] = ft_strdup(env[i]);
		if (NULL == new_env[i])
		{
			while (NULL != new_env[++i])
				free (new_env[i]);
			return (free (variable), free (new_env), ms_perror(MS_E), 1);
		}
	}
	ms_data_env_mset(new_env, data);
	ms_exec_free_av(new_env);
	free (variable);
	return (0);
}

int	ms_data_env_replace_line(char **env, \
					char *variable, char *new_line)
{
	int		i;

	i = 0;
	while (NULL != env[i])
	{
		if (0 == ft_strncmp(variable, env[i], (ft_strlen(variable))) \
		&& '=' == env[i][ft_strlen(variable)])
		{
			free(env[i]);
			env[i] = ft_strdup(new_line);
		}
		i++;
	}
	return (free (variable), 0);
}
