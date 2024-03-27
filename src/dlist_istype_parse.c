/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_istype_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:24:31 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/13 11:24:40 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

int	ms_dlist_istype_pipe_list(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_cmpd(t_dlist *list)
{
	if (MS_TOKEN_OPEN == list->type || MS_TOKEN_CLOSE == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_not_first(t_dlist *list)
{
	if (MS_TOKEN_PIPE == list->type \
		|| MS_TOKEN_AND == list->type || MS_TOKEN_OR == list->type \
		|| MS_TOKEN_CLOSE == list->type)
		return (1);
	return (0);
}

int	ms_dlist_istype_parse(t_dlist *list)
{
	if (MS_PARSE_CMD == list->type \
		|| MS_PARSE_PIPE == list->type || MS_PARSE_LIST == list->type \
		|| MS_PARSE_CMP == list->type)
		return (1);
	return (0);
}
