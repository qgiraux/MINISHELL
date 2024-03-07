/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:54:40 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/07 15:02:40 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERROR_H
# define PARSER_ERROR_H

# include "token.h"
# include "dlist.h"

# define MS_PARSE_CMD 101
# define MS_PARSE_PIPE 102
# define MS_PARSE_LIST 104
# define MS_PARSE_CMP 105

# define MS_OPEN_PARENTH_MSG "syntax error near unexpected token '('\n"
# define MS_CLOSE_PARENTH_MSG "syntax error near unexpected token ')'\n"

int		ms_parser_error(t_dlist *list, void *data);
void	ms_error_write(int type, void *data);

#endif