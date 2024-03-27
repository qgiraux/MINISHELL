/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:56:12 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/22 17:35:35 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_error.h"
#include "token_utils.h"
#include "data.h"
#include "fprintf.h"

/*si erreur de parse, affiche le message necessaire*/
void	ms_error_write(int type, void *data)
{
	t_csd		fprintf_args;
	const char	**operator_arr = ms_data_operator_get(data);
	const char	*s[3] = {MS_E, (char *)operator_arr[type], NULL};

	ms_fprintf_args(NULL, s, NULL, &fprintf_args);
	ms_fprintf(STDERR_FILENO, MS_ETOKEN_MSGS, &fprintf_args);
}
