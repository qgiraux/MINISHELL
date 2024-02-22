/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/20 14:31:30 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "../Libft/libft.h"
# include "dlist.h"
# include "errno.h"

# define MS_TOKEN_WORD -1
# define MS_TOKEN_PIPE 0
# define MS_TOKEN_AND 1
# define MS_TOKEN_OR 2
# define MS_TOKEN_OPEN 3
# define MS_TOKEN_CLOSE 4
# define MS_TOKEN_INTPUT 5
# define MS_TOKEN_OUTPUT 6
# define MS_TOKEN_APPEND 7
# define MS_TOKEN_HERE_DOC 8

# define MS_CONTROL_PIPE "|"
# define MS_CONTROL_AND "&&"
# define MS_CONTROL_OR "||"
# define MS_CONTROL_OPEN "("
# define MS_CONTROL_CLOSE ")"
# define MS_REDIR_INTPUT "<"
# define MS_REDIR_OUTPUT ">"
# define MS_REDIR_APPEND ">>"
# define MS_REDIR_HERE_DOC "<<"

# define MS_QUOTE_1 39
# define MS_QUOTE_2 '"'

typedef struct s_token {
	int		operator;
	char	*word;
}	t_token;

t_dlist		*ms_token_list(char *input, void *data);
void		ms_token_delete(void *content);
const char	**ms_token_get_operator_arr(void *data);

#endif