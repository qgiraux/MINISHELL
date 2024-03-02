/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:37:27 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir_utils.h"

static int	ms_redir_dup2_new(int fid_old, int fid_new)
{
	int	err;

	if (fid_old == STDIN_FILENO \
		|| fid_old == STDOUT_FILENO \
		|| fid_old == STDERR_FILENO \
		|| fid_old <= -1)
		return (0);
	err = dup2(fid_old, fid_new);
	if (-1 == err)
		return (ms_redir_error(NULL, errno, 2, NULL), 1);
	else if (err)
		return (1);
	close(fid_old);
	return (0);
}

int	ms_redir_dup2(void *data)
{
	int	fid_in;
	int	fid_out;

	ms_redir_data_get(&fid_in, &fid_out, data);
	if (ms_redir_dup2_new(fid_in, STDIN_FILENO))
		return (1);
	if (ms_redir_dup2_new(fid_out, STDOUT_FILENO))
		return (1);
	return (0);
}
