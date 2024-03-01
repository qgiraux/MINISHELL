/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:47:21 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 13:18:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/node_type.h"
#include "../includes/parser.h"


int	node_type_cmd(t_dlist *node, const char **data)
{
	print_input(node, data);
	printf("\n");
	return(0);
}