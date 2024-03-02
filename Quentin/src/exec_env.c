/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:48 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_utils.h"

extern char	**environ;

const char	*ms_exec_env_get_line(const char **env, const char *var)
{
	int		line;
	size_t	i;

	line = 0;
	while (env[line])
	{
		i = 0;
		while (env[line][i] == var[i])
			i++;
		if ('=' == env[line][i] && '\0' == var[i])
			return (env[line]);
		line++;
	}
	return (NULL);
}

static char	*ms_exec_env_get_value(const char *env_line, const char *var)
{
	char	*val;
	size_t	len_val;
	size_t	len0;
	size_t	i;

	len0 = ft_strlen(var) + 1;
	len_val = 0;
	i = len0;
	while ('\0' != env_line[i] && '\n' != env_line[i])
		i = len0 + len_val++;
	val = (char *)malloc(sizeof(char) * (len_val + 1));
	if (NULL == val)
		return (NULL); //
	i = 0;
	while (i < len_val)
	{
		val[i] = env_line[len0 + i];
		i++;
	}
	val[i] = '\0';
	return (val);
}

char	*ms_exec_env_get_str(const char **env, const char *var)
{
	char		*value;
	size_t		len_value;
	const char	*line;

	line = ms_exec_env_get_line(env, var);
	if (NULL == line)
		;
	return (ms_exec_env_get_value(line, var));
}

char	**ms_exec_env(void *data)
{
	(void)data;
	return (environ);
}