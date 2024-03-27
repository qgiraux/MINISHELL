/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:31:53 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_utils.h"
#include "data.h"

static int	_dup2_new(int fid_old, int fid_new)
{
	if (fid_old == STDIN_FILENO \
		|| fid_old == STDOUT_FILENO \
		|| fid_old == STDERR_FILENO \
		|| fid_old <= -1)
		return (MS_SUCCESS);
	if (-1 == dup2(fid_old, fid_new))
		return (perror(MS_E), 1);
	close(fid_old);
	return (MS_SUCCESS);
}

/* ms_redir_dup2:
 * Redirect std input and output according to <data>
 * Does nothing is fid is invalid (STDOUT_FILENO, STDIN_FILENO, or neg)
 * Returns an error if dup2 fails
 */
int	ms_redir_dup2(void *data)
{
	int	fid_in;
	int	fid_out;

	ms_data_redir_get(&fid_in, &fid_out, data);
	if (_dup2_new(fid_in, STDIN_FILENO))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (_dup2_new(fid_out, STDOUT_FILENO))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	return (MS_SUCCESS);
}
