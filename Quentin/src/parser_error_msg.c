/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:56:12 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 17:00:41 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_error.h"
#include "token_utils.h"
/*si erreur de parse, affiche le message necessaire*/
void	ms_error_write(int type, void *data)
{
	const char		**operator_arr = ms_token_get_operator_arr((const char **)data);

	ft_putstr_fd(MS_ETOKEN_MSG, 2);
	ft_putstr_fd(" >>'", 2);
	ft_putstr_fd((char *)operator_arr[type], 2);
	ft_putstr_fd("'\n", 2);
}
