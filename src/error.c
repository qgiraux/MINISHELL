/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/28 10:32:17 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fprintf.h"
#include "error.h"
#include "error_utils.h"

/*Prints unnamed error or trace
 * ms_e(__FILE__, __LINE__, 1)
 * Prints an unnamed error when there is no suitable error message
 * ms_e(__FILE__, __LINE__, 0)
 * Prints an unnamed error, useful to trace errors
 */
void	ms_e(char *file, int line, int first_error)
{
	t_csd		args;
	const char	*s[3] = {MS_E, file, NULL};
	const int	d[2] = {line, 0};

	if (first_error || MS_DEBUG_TRACE)
	{
		ms_fprintf_args(NULL, s, d, &args);
		ms_fprintf(STDERR_FILENO, MS_EUNK, &args);
	}
}

/*Prints error in bash format using global var errno
 * Set errno to 0
 * To be used when it is unclear if error from errno has been printed
 */
void	ms_perror(char *str)
{
	if (errno)
		perror(str);
	errno = 0;
}
