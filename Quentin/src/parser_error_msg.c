/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:56:12 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 14:30:35 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dlist.h"
#include "../includes/parser_error.h"
#include "../includes/token.h"
#include "../includes/token_utils.h"

void	ms_error_write(int type, const char **data)
{
	const char		**operator_arr = ms_token_get_operator_arr(data);

	ft_putstr_fd(MS_ETOKEN_MSG, 2);
	ft_putstr_fd(" >>'", 2);
	ft_putstr_fd((char *)operator_arr[type], 2);
	ft_putstr_fd("'\n", 2);
}
