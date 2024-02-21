/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:44:29 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/16 18:10:40 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	**find_path(char **env)
{
	int		i;
	char	*path;
	char	**result;

	i = 0;
	while ((ft_strncmp(env[i], "PATH", 4) != 0))
		i++;
	path = env[i] + 5;
	result = ft_split(path, ':');
	return (result);
}

char	*check_paths(char *str, char **env, int i)
{
	char	**dest;
	char	*res;

	if (access(str, R_OK) == 0)
		return (str);
	dest = find_path(env);
	while (dest[++i])
	{
		res = ft_strdup(dest[i]);
		free(dest[i]);
		dest[i] = ft_strjoin(res, "/");
		free (res);
		res = ft_strdup(dest[i]);
		free(dest[i]);
		dest[i] = ft_strjoin(res, str);
		free(res);
		if (access(dest[i], R_OK) == 0)
		{
			res = ft_strdup(dest[i]);
			free_split(dest);
			return (res);
		}
	}
	free_split(dest);
	return (NULL);
}
