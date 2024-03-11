/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/09 14:20:08 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "error_utils.h"

/* ms_e:
 * Prints unnamed error or trace
 * ms_e(__FILE__, __LINE__, 1)
 * Prints an unnamed error when there is no suitable error message
 * ms_e(__FILE__, __LINE__, 0)
 * Prints an unnamed error, useful to trace errors
 */

void	ms_e(char *file, int line, int first_error)
{
	const int	fd_error = 2;

	if (first_error || MS_DEBUG_TRACE)
	{
		ft_putstr_fd(MS_E, fd_error);
		ft_putstr_fd(ESEP, fd_error);
		ft_putstr_fd(MS_EMSG_UNK, fd_error);
		if (NULL != file)
		{
			ft_putstr_fd(file, fd_error);
			ft_putstr_fd(ESEP, fd_error);
		}
		ft_putnbr_fd(line, fd_error);
		ft_putstr_fd("\n", fd_error);
	}
}

/* ms_error_str:
 * Prints error in bash format using errnum
 * <str>: <strerror(<errnum>)>
 * to be used when errno has been changed or perror can't be used
 */

void	ms_error_str(char *str, int errnum)
{
	const int	fd_error = 2;

	if (NULL != str)
	{
		ft_putstr_fd(str, fd_error);
		ft_putstr_fd(ESEP, fd_error);
	}
	ft_putstr_fd(strerror(errnum), fd_error);
	ft_putstr_fd("\n", fd_error);
}

/* ms_perror:
 * Prints error in bash format using global var errno
 * Set errno to 0
 * To be used when it is unclear if error from errno has been printed
 */

void	ms_perror(char *str)
{
	if (errno)
		perror(str);
	errno = 0;
}
