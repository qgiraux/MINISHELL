/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:10:41 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "exec_utils.h"
#include "env.h"

static char	*ms_get_next_row(char *line, size_t *line_index, char sep)
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
		return (NULL);
	i = 0;
	while (i < len_row)
		row[i++] = line[(*line_index)++];
	row[i] = '\0';
	if ('\0' != line[*line_index])
		(*line_index)++;
	return (row);
}

static char	*ms_exec_bin_path_join(const char *path, const char *bin_name)
{
	const size_t	len_path = ft_strlen(path);
	const size_t	len_bin_name = ft_strlen(bin_name);
	size_t			i_join;
	size_t			i_tot;
	char			*abs_path;

	abs_path = (char *)malloc(sizeof(char) * (len_path + 1 + len_bin_name + 1));
	if (NULL == abs_path)
		return (NULL);
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

char	*ms_exec_bin_path(const char *bin_name, const char **env)
{
	char	*path_line;
	size_t	line_index;
	char	*path;
	char	*abs_path;

	if (ms_env_get_str(env, ENV_PATH, &path_line))
		return (NULL);
	line_index = 0;
	while ('\0' != path_line[line_index])
	{
		path = ms_get_next_row(path_line, &line_index, ENV_PATH_SEP);
		if (NULL == path)
			return (NULL);
		abs_path = ms_exec_bin_path_join(path, bin_name);
		free(path);
		if (NULL == abs_path)
			return (NULL);
		if (0 == access(abs_path, R_OK))
			return (abs_path);
		free(abs_path);
	}
	free(path_line);
	return (NULL);
}
