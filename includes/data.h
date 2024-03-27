/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:53:13 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 17:35:30 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "data_utils.h"
# define MS_NOEXIT -1

void		ms_data_redir_set(int fid_in, int fid_out, void *ptr_data);
void		ms_data_redir_get(int *fid_in, int *fid_out, void *ptr_data);
//
char		*ms_data_exit_pipe_get(void *ptr_data);
void		ms_data_exit_pipe_set(int status, void *ptr_data);
//
int			ms_data_ini_main(char **env, void *data, int (*f)(void *));
int			ms_data_ini_line(void *data);
int			ms_data_ini_cmd(void *data);
void		ms_data_destroy_line(void *data);
void		ms_data_destroy_main(void *data);
void		ms_data_destroy_cmd(void *ptr_data);
//
char		**ms_data_env_get(void *ptr_data);
int			ms_data_env_mset(char **env, void *ptr_data);
//
int			ms_data_exit_shell_get(void *ptr_data);
void		ms_data_exit_shell_set(int status, void *ptr_data);
//
const char	**ms_data_operator_get(void *ptr_data);
//
void		ms_data_files_set(t_dlist *list, void *ptr_data);
t_dlist		*ms_data_files_get(void *ptr_data);
void		ms_data_list_set(t_dlist *list, void *ptr_data);
t_dlist		*ms_data_list_get(void *ptr_data);

#endif
