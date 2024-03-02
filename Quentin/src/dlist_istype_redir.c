/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_istype_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:24 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int	ms_dlist_istype_redir_out(t_dlist *list)
{
	if (MS_TOKEN_OUTPUT == list->type || MS_TOKEN_APPEND == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_redir_in(t_dlist *list)
{
	if (MS_TOKEN_INTPUT == list->type || MS_TOKEN_HERE_DOC == list->type)
		return (1);
	return (0);
}
