/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:39:43 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 15:59:24 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "token.h"
#define MSH "Minishell> "
int	msh_start(char **data, char *input);
void	free_input(t_dlist *list);


#endif