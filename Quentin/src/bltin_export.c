/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:40:02 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 18:53:56 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"


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

static char	*check_paths(char *str, char **env, int i)
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

int	ms_bltin_export(char **av, void *data)
{
	char	**env;

	env = data->env;
	
	if (NULL == av[1])
	{
		while (NULL != env)
		{
			while (NULL != *env)
			{
				write(1, *env, ft_strlen(*env));
				*env++;
			}
			env++;
		}
	}
	else
	{
		
	}
}