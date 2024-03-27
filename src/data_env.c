/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:10:43 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static size_t	_size(char **env)
{
	size_t	n;

	if (NULL == env)
		return (0);
	n = 0;
	while (env[n])
		n++;
	return (n);
}

int	ms_data_env_ini(void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	data->env = NULL;
	return (MS_SUCCESS);
}

void	ms_data_env_destroy(void *ptr_data)
{
	t_data	*data;
	char	**env;
	size_t	i;

	data = (t_data *)ptr_data;
	env = (char **)(data->env);
	if (NULL == env)
		return ;
	i = 0;
	while (env[i])
		free(env[i++]);
	if (env)
		free(env);
	data->env = NULL;
}

char	**ms_data_env_get(void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	return (data->env);
}

int	ms_data_env_mset(char **env, void *ptr_data)
{
	const size_t	n = _size(env);
	t_data			*data;
	char			**env_cpy;
	char			*line;
	size_t			i;

	ms_data_env_destroy(ptr_data);
	data = (t_data *)ptr_data;
	env_cpy = (char **)malloc(sizeof(char *) * (n + 1));
	if (NULL == env_cpy)
		return (ms_perror(MS_E), 1);
	data->env = env_cpy;
	i = 0;
	while (i < n)
	{
		env_cpy[i] = NULL;
		line = ft_strdup(env[i]);
		if (NULL == line)
			return (ms_perror(MS_E), ms_data_env_destroy(ptr_data), 1);
		env_cpy[i++] = line;
	}
	env_cpy[i] = NULL;
	data->env = env_cpy;
	return (MS_SUCCESS);
}
