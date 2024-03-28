/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/28 17:22:38 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "../Libft/libft.h"
# include "errno.h"
# include "error.h"
# include "token.h"

# define MS_METACHAR " \t\n|&()<>"
# define MS_BLANK " \t"
# define MS_METACHAR_NOT_BLANK "|&()<>"

# define MS_TOKEN_ESOURCE "MSH"

# define MS_EQUOTE 256
# define MS_EQUOTE_MSG "%s: syntax error unclosed quote: %c\n"

# define MS_ETOKEN 257
# define MS_ETOKEN_MSGC "%s: syntax error near unexpected token `%c'\n"
# define MS_ETOKEN_MSGS "%s: syntax error near unexpected token `%s'\n"

char	*ms_token_strchr(const char *s, int c, int *quote);
void	ms_token_error(char chr, int errnum, int fd_error);
int		ms_token_get_operator(char **input, void *data);
int		ms_token_add_operator(\
			t_dlist **tokens, char **input, void *data);
int		ms_token_add_word(\
			t_dlist **tokens, char **input, int *quote);

#endif