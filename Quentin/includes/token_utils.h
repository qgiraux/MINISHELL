/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/20 18:03:38 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "../Libft/libft.h"
# include "errno.h"
# include "../includes/token.h"

# define MS_METACHAR " \t\n|&()<>"
# define MS_BLANK " \t"
# define MS_METACHAR_NOT_BLANK "|&()<>"

# define MS_TOKEN_ESOURCE "bash"

# define MS_EQUOTE 256
# define MS_EQUOTE_MSG "syntax error unclosed quote"

# define MS_ETOKEN 257
# define MS_ETOKEN_MSG "syntax error near unexpected token"

char	*ms_token_strchr(const char *s, int c, int *quote);
void	ms_token_error(void *arg, int errnum, int fd_error);
int		ms_token_get_operator(char **input, void *data);
int		ms_token_add_operator(\
			t_dlist **tokens, char **input, void *data);
int		ms_token_add_word(\
			t_dlist **tokens, char **input, int *quote);

#endif