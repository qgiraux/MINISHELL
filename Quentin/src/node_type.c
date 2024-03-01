/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:13 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 16:42:28 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/node_type.h"
#include "../includes/parser.h"


int	node_type(t_dlist *node, int status, const char **data)
{	
	if (MS_PARSE_LIST == node->type)
	{
		status = node_type_list(node, status, data);
	}
	if (MS_PARSE_CMP == node->type)
	{

		status = node_type_compound(node, status, data);
	}
	if (MS_PARSE_PIPE == node->type)
	{
		status = node_type_pipe(node, status, data);
	}
	if (MS_PARSE_CMD == node->type)
	{
		printf("\ncommand\n");
		print_input(node, data);
		status = node_type_cmd(node, data);
	}
	return (status);
}