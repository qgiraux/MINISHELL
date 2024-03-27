/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/13 18:07:44 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_UTILS_H
# define DATA_UTILS_H

# include "dlist.h"
# include "error.h"
# include <stddef.h>
# include "libft.h"

typedef struct s_data
{
	char	**operator;
	char	**env;
	int		fd_in;
	int		fd_out;
	char	pipe_exit_status[4];
	int		shell_status;
	t_dlist	*list;
	t_dlist	*files;
}		t_data;

int		ms_data_redir_ini(void *ptr_data);
void	ms_data_redir_destroy(void *ptr_data);
//
int		ms_data_exit_pipe_ini(void *ptr_data);
//
int		ms_data_env_ini(void *ptr_data);
void	ms_data_env_destroy(void *ptr_data);
//
int		ms_data_exit_shell_ini(void *ptr_data);
//
void	ms_data_list_ini(void *ptr_data);
void	ms_data_list_destroy(void *ptr_data);
void	ms_data_files_ini(void *ptr_data);
void	ms_data_files_destroy(void *ptr_data);
void	ms_data_operator_set(char **operator, void *ptr_data);

#endif
