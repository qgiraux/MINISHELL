/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:13 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 11:01:54 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "exec.h"
#include "data.h"

/*dispatch dansles fonctions appropriees 
*selon le type de noeud sur lequel on est actuellement*/
int	ms_node(t_dlist *node, int status, void *data)
{
	if (0 != errno)
		return (errno);
	if (NULL != node && MS_PARSE_LIST == node->type)
		status = ms_node_list(node, status, data);
	else if (NULL != node && MS_PARSE_CMP == node->type)
		status = ms_node_compound(node, status, data);
	else if (NULL != node && MS_PARSE_PIPE == node->type)
		status = ms_node_pipe(node, status, data);
	else if (NULL != node && MS_PARSE_CMD == node->type)
		status = ms_exec_cmd((t_dlist **)&node->content, data);
	return (status);
}
