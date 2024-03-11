/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:51:44 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/08 13:20:51 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

extern char	**environ;

static char	*ms_env_mget_value(const char *env_line, const char *var)
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
		return (ms_perror(MS_E), NULL);
	i = 0;
	while (i < len_val)
	{
		val[i] = env_line[len0 + i];
		i++;
	}
	val[i] = '\0';
	return (val);
}

/* ms_env_get_line:
 * Get pointer to <var>=<value> from env
 * Pointer should no be modified or free'd
 * Returns the pointer
 */

const char	*ms_env_get_line(const char **env, const char *var)
{
	int		line;
	size_t	i;

	if (NULL == env || NULL == var)
		return (NULL);
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

/* ms_env_mget_str:
 * Get malloc'ed <value> from corresponding <var> in env
 * <value> is a copy that should be free'd
 * <value> is a copy of "" if <var> not in env or env is NULL
 * <value> is NULL iff malloc error
 * Returns 1 if error and print a message
 */

int	ms_env_mget_str(const char **env, const char *var, char **value)
{
	const char	*line;

	*value = NULL;
	line = ms_env_get_line(env, var);
	if (NULL == line)
		*value = ft_strdup("");
	else
		*value = ms_env_mget_value(line, var);
	if (NULL == *value)
		return (ms_perror(MS_E), 1);
	return (MS_SUCCESS);
}

/* ms_env:
 * WIP
 */

char	**ms_env(void *data)
{
	(void)data; // TMP
	return (environ);
}
