/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:11:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	_close(int *fid)
{
	if (fid \
		&&*fid != STDIN_FILENO \
		&& *fid != STDOUT_FILENO \
		&& *fid != STDERR_FILENO \
		&& *fid > -1)
		close(*fid);
	*fid = -1;
}

void	ms_data_redir_set(int fid_in, int fid_out, void *ptr_data)
{
	t_data	*data;

	if (NULL == ptr_data)
		return ;
	data = (t_data *)ptr_data;
	if (-1 < fid_in)
		data->fd_in = fid_in;
	if (-1 < fid_out)
		data->fd_out = fid_out;
}

void	ms_data_redir_get(int *fid_in, int *fid_out, void *ptr_data)
{
	t_data	*data;

	if (NULL == ptr_data)
		return ;
	data = (t_data *)ptr_data;
	if (fid_in)
		*fid_in = data->fd_in;
	if (fid_out)
		*fid_out = data->fd_out;
}

int	ms_data_redir_ini(void *ptr_data)
{
	t_data	*data;

	if (NULL == ptr_data)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	data = (t_data *)ptr_data;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	return (MS_SUCCESS);
}

void	ms_data_redir_destroy(void *ptr_data)
{
	t_data	*data;

	if (NULL == ptr_data)
		return ;
	data = (t_data *)ptr_data;
	_close(&data->fd_in);
	_close(&data->fd_out);
}
