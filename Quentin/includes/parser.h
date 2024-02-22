/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:28:06 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/22 12:51:48 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"

# define MS_PARSE_CMD 10
# define MS_PARSE_PIPE 11
# define MS_PARSE_LIST 12
# define MS_PARSE_CMP 13


void	ms_interpreter(char *input);
t_dlist	*ms_cmd_list(t_dlist *token);
t_dlist	*ms_pipeline(t_dlist *cmd);
t_dlist	*ms_list(t_dlist *cmd);
void 	print_input(t_dlist *list, const char **data);

#endif