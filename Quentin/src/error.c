/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/02 11:16:13 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_utils.h"

void	ms_error(char *str, char *file, int line, int first_error)
{
	const int	fd_error = 2;

	if (first_error || MS_DEBUG_TRACE)
	{
		if (NULL != str)
		{
			ft_putstr_fd(str, fd_error);
			ft_putstr_fd(": ", fd_error);
		}
		ft_putstr_fd(MS_EMSG_UNK, fd_error);
		if (NULL != file)
		{
			ft_putstr_fd(file, fd_error);
			ft_putstr_fd(":", fd_error);
		}
		ft_putnbr_fd(line, fd_error);
		ft_putstr_fd("\n", fd_error);
	}
}
