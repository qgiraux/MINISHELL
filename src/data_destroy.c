/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/27 13:22:44 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "readline.h"

void	ms_data_destroy_cmd(void *ptr_data)
{
	ms_data_redir_destroy(ptr_data);
	ms_data_files_destroy(ptr_data);
}

void	ms_data_destroy_line(void *ptr_data)
{
	ms_data_list_destroy(ptr_data);
	ms_data_destroy_cmd(ptr_data);
}

/* ms_data_destroy_main:
 * Destroyes <data> and clear readline buffers
 */
void	ms_data_destroy_main(void *data)
{
	ms_readline_clear();
	ms_data_destroy_line(data);
	ms_data_env_destroy(data);
}
