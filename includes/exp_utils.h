/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/29 10:00:13 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_UTILS_H
# define EXP_UTILS_H

# include "dlist.h"
# include "libft.h"
# include "error.h"
# include <sys/types.h>
# include <dirent.h>

# define EXP_ESC 92
# define EXP_VAR '$'
# define EXP_UNDERSCORE '_'
# define EXP_SPE0 '?'
# define EXP_ESC_LIST "\\\"\'"

# define MS_PARA_STR 1000
# define MS_PARA_NAME 1001
# define MS_PARA_SPE0 1002
# define MS_PARA_QUOTE1 1003
# define MS_PARA_QUOTE2_OPEN 1004
# define MS_PARA_QUOTE2_CLOSE 1005
# define MS_PARA_ESC_ME 1006
# define MS_PARA_CONST_STR 1007
# define MS_PARA_ERROR 1008

# define EXP_WILD '*'
# define EXP_CWD "."
# define EXP_DOT '.'

int		ms_parameter_var(char *s, size_t *len, int *type);
int		ms_parameter_quote(char *s, size_t *len, int *type, char *quote);
char	*ms_exp_escape(char *str, char *list);
char	*ms_exp_escape_removal(char *str, char *lst);
int		ms_exp_parameter_replace(t_dlist *curr, char **env, void *data);
char	*ms_exp_parameter(char *input, char **env, void *data);
int		ms_exp_filename(t_dlist **escaped_tokens, t_dlist **next, void *data);
int		ms_exp_filename_list_cwd(void *data);
char	*ms_exp_escape_dup(char *str, char *to_escape);
char	*exp_parameter_escape(char *big, size_t len_str, int type);

#endif