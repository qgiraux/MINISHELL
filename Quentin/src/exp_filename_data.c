/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/05 16:46:11 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"

t_dlist	*ms_data_cwd_list_get(void *data)
{
	return ((t_dlist *)data);
}

void	ms_data_cwd_list_set(t_dlist **files, void **data)
{
	if (NULL == data || NULL == files)
		return ;
	*data = (void *)*files;
}

void	ms_data_cwd_list_destroy(void *data)
{
	t_dlist	*list;

	list = ms_data_cwd_list_get(data);
	if (NULL == list)
		return ;
	ms_dlstclear(&list); //
}

void	ms_data_cwd_list_ini(void *data)
{
	(void)data;
	; //
}
