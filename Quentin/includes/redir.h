/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/29 14:01:31 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "dlist.h"

int		ms_redir_save(t_dlist **list, void *data);
int		ms_redir_dup2(void *data);
void	ms_redir_data_set(int fid_in, int fid_out, void *data);
void	ms_redir_data_get(int *fid_in, int *fid_out, void *data);
void	ms_redir_data_ini(void **data);
void	ms_redir_data_destroy(void **data);
//void	debug_data_read(void *data);

#endif