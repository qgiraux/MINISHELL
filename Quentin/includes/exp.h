/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/05 16:16:54 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_H
# define EXP_H

# include "dlist.h"

char	*ms_exp_parameter(char *input, char **env, void *data);
int		ms_exp(t_dlist **head, void *data);
void	ms_data_cwd_list_destroy(void *data);
void	ms_data_cwd_list_ini(void *data);

#endif