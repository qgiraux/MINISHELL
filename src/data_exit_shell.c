/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_exit_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 17:36:02 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	ms_data_exit_shell_get(void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	return (data->shell_status);
}

void	ms_data_exit_shell_set(int status, void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	data->shell_status = status;
}

int	ms_data_exit_shell_ini(void *ptr_data)
{
	ms_data_exit_shell_set(MS_NOEXIT, ptr_data);
	return (MS_SUCCESS);
}
