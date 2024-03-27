/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_exit_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/12 15:08:25 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

char	*ms_data_exit_pipe_get(void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	return (data->pipe_exit_status);
}

void	ms_data_exit_pipe_set(int status, void *ptr_data)
{
	const int	nbase = 10;
	const char	*base = "0123456789";
	char		*str_status;
	size_t		i;
	int			tmp;

	str_status = ((t_data *)ptr_data)->pipe_exit_status;
	status = status & 0xFF;
	i = 0;
	if (status < nbase)
		str_status[i++] = base[status];
	else if (status < nbase * nbase)
	{
		str_status[i++] = base[status / nbase];
		str_status[i++] = base[status % nbase];
	}
	else
	{
		tmp = status / nbase;
		str_status[i++] = base[tmp / nbase];
		str_status[i++] = base[tmp % nbase];
		str_status[i++] = base[status % nbase];
	}
	str_status[i] = '\0';
}

int	ms_data_exit_pipe_ini(void *ptr_data)
{
	ms_data_exit_pipe_set(0, ptr_data);
	return (MS_SUCCESS);
}
