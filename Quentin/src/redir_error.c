/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:17:27 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_utils.h"

void	ms_redir_error(void *arg, int errnum)
{
	if (errnum == EREDIR_BADWORD && arg)
	{
		ft_putstr_fd(MS_E, STDERR_FILENO);
		ft_putstr_fd(ESEP, STDERR_FILENO);
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd(ESEP, STDERR_FILENO);
		ft_putstr_fd(EREDIR_BADWORD_MSG, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		ms_e(__FILE__, __LINE__, 1); //
}
