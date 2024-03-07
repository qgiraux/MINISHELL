/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:51:44 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/06 11:26:56 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern char	**environ;

const char	*ms_env_get_line(const char **env, const char *var)
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

static char	*ms_env_get_value(const char *env_line, const char *var)
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

int	ms_env_get_str(const char **env, const char *var, char **value)
{
	const char	*line;

	*value = NULL;
	line = ms_env_get_line(env, var);
	if (NULL == line)
		return (0);
	*value = ms_env_get_value(line, var);
	if (NULL == *value)
		return (1);
	return (0);
}

char	**ms_env(void *data)
{
	(void)data;
	return (environ);
}
