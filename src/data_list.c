/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/12 15:09:01 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	ms_data_list_set(t_dlist *list, void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	data->list = list;
}

t_dlist	*ms_data_list_et(void *ptr_data)
{
	return ((t_dlist *)(((t_data *)ptr_data)->list));
}

void	ms_data_list_ini(void *ptr_data)
{
	ms_data_list_set(NULL, ptr_data);
}

void	ms_data_list_destroy(void *ptr_data)
{
	t_data	*data;
	t_dlist	*lst;

	data = (t_data *)ptr_data;
	lst = (t_dlist *)(data->list);
	ms_dlstclear(&lst);
	data->list = NULL;
}
