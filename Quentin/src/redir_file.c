/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:15:00 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here.h"
#include "redir_utils.h"

static int	ms_redir_file_close(int *fid)
{
	if (*fid \
		&& *fid != STDIN_FILENO \
		&& *fid != STDOUT_FILENO \
		&& *fid != STDERR_FILENO \
		&& *fid > -1)
	{
		if (-1 == close(*fid))
			return (ms_redir_error(NULL, errno, 2, NULL), 1);
	}
	*fid = -1;
	return (0);
}

int	ms_redir_file_close_all(void *data)
{
	int	fid_in;
	int	fid_out;
	int	is_err;

	is_err = 0;
	ms_redir_data_get(&fid_in, &fid_out, data);
	is_err = is_err | ms_redir_file_close(&fid_in);
	is_err = is_err | ms_redir_file_close(&fid_out);
	return (is_err);
}

int	ms_redir_file_out(int *fid, void *data, char *pathname, int append_mode)
{
	if (ms_redir_file_close(fid))
		return (1);
	if (append_mode)
		append_mode = O_APPEND;
	else
		append_mode = O_TRUNC;
	*fid = open(pathname, \
		O_RDWR | O_CREAT | append_mode, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == *fid)
		return (ms_redir_error(NULL, errno, 2, NULL), 1);
	ms_redir_data_set(-1, *fid, data);
	return (0);
}

int	ms_redir_file_in(int *fid, void *data, char *pathname)
{
	if (ms_redir_file_close(fid))
		return (1);
	*fid = open(pathname, O_RDONLY, S_IRUSR);
	if (-1 == *fid)
		return (ms_redir_error(NULL, errno, 2, NULL), 1);
	ms_redir_data_set(*fid, -1, data);
	return (0);
}

int	ms_redir_file_here(int *fid, void *data, char *delimiter)
{
	*fid = open(MS_HERE_PATH, \
		O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == *fid)
		return (ms_redir_error(NULL, errno, 2, NULL), 1);
	if (ms_here(*fid, delimiter))
		return (1); //
	if (close(*fid))
		return (1); //
	*fid = open(MS_HERE_PATH, O_RDONLY, S_IRUSR);
	ms_redir_data_set(*fid, -1, data);
	return (0);
}
