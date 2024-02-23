/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:28:06 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 11:57:51 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
#include "dlist.h"

# define MS_PARSE_CMD 10
# define MS_PARSE_PIPE 11
# define MS_PARSE_LIST 12
# define MS_PARSE_CMP 13


void	ms_interpreter(char *input);
int		ms_cmd_list(t_dlist *token);
int		ms_pipeline(t_dlist *cmd);
int		ms_list(t_dlist *cmd);
void 	print_input(t_dlist *list, const char **data);
int		ms_compound(t_dlist *pipe);

#endif