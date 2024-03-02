/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:17 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec_utils.h"

void	ms_exec_error(void *arg, int errnum, int fd_error, void *data)
{
	if (errno == errnum)
		return (perror(MS_EXEC_ESOURCE));
	ft_putstr_fd(MS_EXEC_ESOURCE, fd_error);
	ft_putstr_fd(": ", fd_error);
	if (MS_EUNKNWN == errnum)
	{
		ft_putstr_fd(MS_EXEC_MSG, fd_error);
		ft_putstr_fd(":", fd_error);
		ft_putstr_fd((char *)arg, fd_error);
	}
	ft_putstr_fd("\n", fd_error);
}
