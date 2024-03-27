/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/12 16:43:08 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	ms_data_operator_set(char **operator, void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	data->operator = operator;
}

const char	**ms_data_operator_get(void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	return ((const char **)(data->operator));
}
