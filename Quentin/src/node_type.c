/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:13 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/02 13:52:12 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/node_type.h"
#include "../includes/parser.h"


int	node_type(t_dlist *node, int status, const char **data)
{	
	if (MS_PARSE_LIST == node->type && 0 == status)
	{
		status = node_type_list(node, status, data);
	}
	if (MS_PARSE_CMP == node->type && 0 == status)
	{

		status = node_type_compound(node, status, data);
	}
	if (MS_PARSE_PIPE == node->type && 0 == status)
	{
		status = node_type_pipe(node, status, data);
	}
	if (MS_PARSE_CMD == node->type && 0 == status)
	{
		write(1, "\ncommand\n", 9);
		print_input(node->content, data);
		write(1, "\n", 1);
		status = 1;
	}
	return (status);
}