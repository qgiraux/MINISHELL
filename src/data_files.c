/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 14:43:08 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	ms_data_files_set(t_dlist *files, void *ptr_data)
{
	t_data	*data;

	data = (t_data *)ptr_data;
	data->files = files;
}

t_dlist	*ms_data_files_get(void *ptr_data)
{
	return ((t_dlist *)(((t_data *)ptr_data)->files));
}

void	ms_data_files_ini(void *ptr_data)
{
	ms_data_files_set(NULL, ptr_data);
}

void	ms_data_files_destroy(void *ptr_data)
{
	t_data	*data;
	t_dlist	*lst;

	data = (t_data *)ptr_data;
	lst = (t_dlist *)(data->files);
	if (NULL != lst)
		ms_dlstclear(&lst);
	data->files = NULL;
}
