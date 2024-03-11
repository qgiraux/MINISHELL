/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:17:27 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "exec_utils.h"
#include "env.h"

static char	*ms_exec_bin_path_mget_row(\
	char *line, size_t *line_index, char sep)
{
	size_t	len_row;
	size_t	i;
	char	*row;

	len_row = 0;
	while ('\0' != line[*line_index + len_row] \
		&& sep != line[*line_index + len_row])
		len_row++;
	row = (char *)malloc(sizeof(char) * (len_row + 1));
	if (NULL == row)
		return (ms_perror(MS_E), NULL);
	i = 0;
	while (i < len_row)
		row[i++] = line[(*line_index)++];
	row[i] = '\0';
	if ('\0' != line[*line_index])
		(*line_index)++;
	return (row);
}

static char	*ms_exec_bin_path_mjoin(const char *path, const char *bin_name)
{
	const size_t	len_path = ft_strlen(path);
	const size_t	len_bin_name = ft_strlen(bin_name);
	size_t			i_join;
	size_t			i_tot;
	char			*abs_path;

	abs_path = (char *)malloc(sizeof(char) * (len_path + 1 + len_bin_name + 1));
	if (NULL == abs_path)
		return (ms_perror(MS_E), NULL);
	i_tot = 0;
	i_join = 0;
	while (i_join < len_path)
		abs_path[i_tot++] = path[i_join++];
	abs_path[i_tot++] = PATH_SEP;
	i_join = 0;
	while (i_join < len_bin_name)
		abs_path[i_tot++] = bin_name[i_join++];
	abs_path[i_tot] = '\0';
	return (abs_path);
}

int	ms_exec_bin_mget_path(\
	char **bin_path, const char *bin_name, const char **env)
{
	char	*path;
	char	*line;
	size_t	line_index;

	if (ms_env_mget_str(env, ENV_PATH, &line))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	line_index = 0;
	while ('\0' != line[line_index])
	{
		path = ms_exec_bin_path_mget_row(line, &line_index, ENV_PATH_SEP);
		if (NULL == path)
			return (free(line), ms_e(__FILE__, __LINE__, 0), 1);
		*bin_path = ms_exec_bin_path_mjoin(path, bin_name);
		free(path);
		if (NULL == *bin_path)
			return (free(line), ms_e(__FILE__, __LINE__, 0), 1);
		if (0 == access(*bin_path, R_OK))
			return (free(line), MS_SUCCESS);
		free(*bin_path);
	}
	*bin_path = NULL;
	return (free(line), MS_SUCCESS);
}
