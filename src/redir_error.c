/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/22 17:42:04 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_utils.h"
#include "fprintf.h"

void	ms_redir_error(char *str)
{
	t_csd		fprintf_args;
	const char	*s[3] = {MS_E, str, NULL};

	ms_fprintf_args(NULL, s, NULL, &fprintf_args);
	ms_fprintf(STDERR_FILENO, EREDIR_BADWORD_MSG, &fprintf_args);
}
