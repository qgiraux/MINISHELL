/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:28:06 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/28 15:57:15 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "dlist.h"

# define MS_PARSE_CMD 101
# define MS_PARSE_PIPE 102
# define MS_PARSE_PIPE0 101
# define MS_PARSE_LIST 104
# define MS_PARSE_CMP 105
# define MS_PARSE_CMP0 104

int		ms_parser_error(t_dlist *list, const char **data);
t_dlist	*ms_interpreter(char *input, const char **data);
int		ms_cmd(t_dlist *token);
int		ms_pipeline(t_dlist *cmd);
int		ms_list(t_dlist *cmd);
void	print_input(t_dlist *list, const char **data);
int		ms_compound(t_dlist *pipe);

#endif