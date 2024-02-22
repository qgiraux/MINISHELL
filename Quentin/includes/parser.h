/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:28:06 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/21 15:47:48 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"

# define MS_PARSE_CMD 10
# define MS_PARSE_PIPE 11
# define MS_PARSE_LIST 12
# define MS_PARSE_CMP 13


t_dlist	*ms_cmd_list(t_dlist *token);
t_dlist	*ms_pipeline(t_dlist *cmd);
t_dlist	*ms_list(t_dlist *cmd);

#endif