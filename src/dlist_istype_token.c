/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_istype_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:24:31 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/28 10:23:02 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ms_dlist_istype_word(t_dlist *list)
{
	if (MS_TOKEN_WORD == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_redir(t_dlist *list)
{
	if (MS_TOKEN_INTPUT == list->type || MS_TOKEN_OUTPUT == list->type \
		|| MS_TOKEN_APPEND == list->type || MS_TOKEN_HERE_DOC == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_operator(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type \
		|| MS_TOKEN_INTPUT == list->type || MS_TOKEN_OUTPUT == list->type \
		|| MS_TOKEN_APPEND == list->type || MS_TOKEN_HERE_DOC == list->type \
		)
		return (1);
	return (0);
}
