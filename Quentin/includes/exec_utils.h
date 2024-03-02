/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/29 13:59:32 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "exec.h"
# include "token.h"
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>

# define ENV_PATH "PATH"
# define ENV_PATH_SEP ':'
# define PATH_SEP '/'
# define MS_EXEC_BACKSLASH '\\'
# define MS_N_BUILTIN 7
# define MS_BUILTIN_ECHO "echo"
# define MS_BUILTIN_CD "cd"
# define MS_BUILTIN_PWD "pwd"
# define MS_BUILTIN_EXPORT "export"
# define MS_BUILTIN_UNSET "unset"
# define MS_BUILTIN_ENV "env"
# define MS_BUILTIN_EXIT "exit"
# define MS_EXEC_ESOURCE "bash"
# define MS_EXEC_MSG "unnamed error in:"
# define MS_EUNKNWN 256

//
char	**ms_exec_env(void *data);
char	*ms_exec_env_get_str(const char **env, const char *var);
//
int		ms_exec_bin(char **av, char **env, void *data);
//
int		ms_exec_builtin(int builtin_id, char **av, char **env, void *data);
int		ms_exec_builtin_id(char *cmd_name);
//
char	**ms_exec_dlist_to_av(t_dlist *list);
//
void	ms_exec_error(void *arg, int errnum, int fd_error, void *data);
//
int		ms_exec_av(char **av, char **env, void *data);
//

#endif