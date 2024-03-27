/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:54:40 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 17:00:33 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERROR_H
# define PARSER_ERROR_H

# include "parser.h"

# define MS_OPEN_PARENTH_MSG "syntax error near unexpected token '('\n"
# define MS_CLOSE_PARENTH_MSG "syntax error near unexpected token ')'\n"

int		ms_parser_error(t_dlist *list, void *data);
void	ms_error_write(int type, void *data);

#endif