/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_pipe_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:13:42 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 11:18:10 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_PIPE_UTILS_H
# define  NODE_PIPE_UTILS_H

int		ms_pipe_loop_close(pid_t pid, void *data);
void	ms_exit_pipe(char *error, void *data, int exit_code);
int		ms_loop_close_init(t_dlist *list, pid_t *pid, void *data, int i);

#endif