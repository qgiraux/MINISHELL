/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/09 14:20:43 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <errno.h>

# define MS_E "ms"
# define ESEP ": "
# define MS_SUCCESS 0

void	ms_e(char *file, int line, int first_error);
void	ms_error_str(char *str, int errnum);
void	ms_perror(char *str);

#endif
