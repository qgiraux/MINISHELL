/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:28:06 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 16:52:12 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "dlist.h"

# define MS_PARSE_CMD 101
# define MS_PARSE_PIPE 102
# define MS_PARSE_LIST 104
# define MS_PARSE_CMP 105

t_dlist	*ms_interpreter(char *input, void *data);
int		ms_cmd(t_dlist *token);
int		ms_pipeline(t_dlist *cmd);
int		ms_list(t_dlist *cmd);
int		ms_compound(t_dlist *pipe);
int		ms_parse_here(t_dlist *token);

#endif