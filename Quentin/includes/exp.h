/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/08 16:39:07 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_H
# define EXP_H

# include "dlist.h"

char	*ms_exp_parameter(char *input, char **env, void *data);
int		ms_exp(t_dlist **head, void *data);
int		ms_exp_str(const char *str, t_dlist **exp, void *data);
void	ms_data_cwd_list_destroy(void *data);
void	ms_data_cwd_list_ini(void *data);

#endif