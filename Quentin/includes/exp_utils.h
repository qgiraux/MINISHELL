/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/05 16:36:33 by jerperez         ###   ########.fr       */
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
# define EXP_SPE0 '*'
# define EXP_ESC_LIST "\\\"\'"

# define MS_PARA_STR 1000
# define MS_PARA_NAME 1001
# define MS_PARA_SPE0 1002
# define MS_PARA_QUOTE1 1003
# define MS_PARA_QUOTE2 1004
# define MS_PARA_ESC 1005
# define MS_PARA_CONST_STR 1006
# define MS_PARA_ERROR 1007

# define EXP_WILD '*'
# define EXP_CWD "."
# define EXP_DOT '.'

int		ms_parameter_var(char *s, size_t *len, int *type);
int		ms_parameter_str_add(\
	t_dlist **values, char *big, size_t len_str, int type);
int		ms_parameter_quote(char *s, size_t *len, int *type);
char	*ms_exp_escape(char *str, char *list);
char	*ms_exp_escape_removal(char *str, char *lst);
int		ms_exp_parameter_replace(t_dlist *curr, char **env, void *data);
char	*ms_exp_parameter(char *input, char **env, void *data);
int		ms_exp_filename(t_dlist **escaped_tokens, void *data);
int		ms_exp_filename_list_cwd(t_dlist **files, void *data);

t_dlist	*ms_data_cwd_list_get(void *data);
void	ms_data_cwd_list_set(t_dlist **files, void **data);

#endif