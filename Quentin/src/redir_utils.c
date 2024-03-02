/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:37:37 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir_utils.h"

void	ms_redir_error(void *arg, int errnum, int fd_error, void *data)
{
	(void)arg;
	(void)data;

	if (errno == errnum)
		return (perror(MS_REDIR_ESOURCE));
	ft_putstr_fd(MS_REDIR_ESOURCE, fd_error);
	ft_putstr_fd(": ", fd_error);
	if (MS_EREDIR == errnum)
	{
		ft_putstr_fd(MS_REDIR_ESOURCE, fd_error); //
		ft_putstr_fd(":", fd_error);
		ft_putstr_fd((char *)arg, fd_error);
	}
	ft_putstr_fd("\n", fd_error);
}
