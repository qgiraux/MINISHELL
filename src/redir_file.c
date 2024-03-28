/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/28 11:28:04 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here.h"
#include "redir_utils.h"
#include "data.h"
#include "fprintf.h"

static void	_error(char *pathname, int errnum)
{
	t_csd		args;
	const char	*s[4] = {MS_E, pathname, strerror(errnum), NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(2, "%s: %s: %s\n", &args);
}

static int	_close(int fid)
{
	if (fid != STDIN_FILENO \
		&& fid != STDOUT_FILENO \
		&& fid != STDERR_FILENO \
		&& fid > -1)
	{
		if (-1 == close(fid))
			return (ms_perror(MS_E), 1);
	}
	return (MS_SUCCESS);
}

int	ms_redir_file_out(int *fid, void *data, char *pathname, int append_mode)
{
	if (_close(*fid))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (append_mode)
		append_mode = O_APPEND;
	else
		append_mode = O_TRUNC;
	*fid = open(pathname, \
		O_RDWR | O_CREAT | append_mode, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == *fid)
		return (_error(pathname, errno), errno = 0, 1);
	ms_data_redir_set(-1, *fid, data);
	return (MS_SUCCESS);
}

int	ms_redir_file_in(int *fid, void *data, char *pathname)
{
	if (_close(*fid))
		return (1);
	*fid = open(pathname, O_RDONLY, S_IRUSR);
	if (-1 == *fid)
		return (_error(pathname, errno), errno = 0, 1);
	ms_data_redir_set(*fid, -1, data);
	return (MS_SUCCESS);
}

int	ms_redir_file_here(int *fid, void *data, char *delimiter)
{
	*fid = open(MS_HERE_PATH, \
		O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == *fid)
		return (ms_perror(MS_E), 1);
	if (ms_here(*fid, delimiter))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (close(*fid))
		return (ms_perror(MS_E), 1);
	*fid = open(MS_HERE_PATH, O_RDONLY, S_IRUSR);
	ms_data_redir_set(*fid, -1, data);
	return (MS_SUCCESS);
}
