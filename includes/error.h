/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/29 14:47:44 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <errno.h>

# define MS_E "ms"
# define MS_SUCCESS 0
# define MS_EXIT_FATAL_SIG 128
# define MS_EXIT_NOT_FOUND 127
# define MS_EXIT_NOT_EXE 126
# define MS_EXIT_BLTIN_BAD_ARG 2

# ifndef MS_DEBUG_DISABLE_TTYCHECK
#  define MS_DEBUG_DISABLE_TTYCHECK 0
# endif

# ifndef MS_DEBUG_TRACE
#  define MS_DEBUG_TRACE 0
# endif

void	ms_e(char *file, int line, int first_error);
void	ms_perror(char *str);

#endif
