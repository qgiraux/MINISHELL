/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:13 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/06 11:54:46 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"
#include "../includes/exec.h"

int	node_type(t_dlist *node, int status, const char **data)
{
	void	*data_exec;

	data_exec = NULL;
	if (NULL != node && MS_PARSE_LIST == node->type && 0 == status)
		status = node_type_list(node, status, data);
	if (NULL != node && MS_PARSE_CMP == node->type && 0 == status)
		status = node_type_compound(node, status, data);
	if (NULL != node && MS_PARSE_PIPE == node->type && 0 == status)
		status = node_type_pipe(node, status, data);
	if (NULL != node && MS_PARSE_CMD == node->type && 0 == status)
		status = ms_exec_cmd(node->content, data_exec);
	return (status);
}
