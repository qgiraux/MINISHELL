/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:13 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 13:07:15 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node_type.h"
#include "exec.h"
/*dispatch dansles fonctions appropriees 
*selon le type de noeud sur lequel on est actuellement*/
int	ms_node_type(t_dlist *node, int status, void*data)
{
	void	*data_exec;

	data_exec = NULL;
	if (NULL != node && MS_PARSE_LIST == node->type)
		status = ms_node_type_list(node, status, data);
	else if (NULL != node && MS_PARSE_CMP == node->type)
		status = ms_node_type_compound(node, status, data);
	else if (NULL != node && MS_PARSE_PIPE == node->type)
		status = ms_node_type_pipe(node, status, data);
	else if (NULL != node && MS_PARSE_CMD == node->type)
		status = ms_exec_cmd(node->content, data_exec);
	//printf("\n exit code : %d\n type code : %d\n", status, node->type);
	return (status);
}
