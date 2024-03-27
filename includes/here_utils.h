/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 13:19:40 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_UTILS_H
# define HERE_UTILS_H

# include "libft.h"
# include "dlist.h"
# include <unistd.h>
# include <errno.h>
# include "error.h"
# include <dirent.h>

# define MS_TMP_FOLDER "/tmp"
# define MS_HERE_FILE "minishell-heredoc-"

# define READ_BUFF_LEN 100
# define MS_WEOF 500
# define MS_HERE_LINE "> "
# define MS_WHERE_MSG "warning: here-document delimited by end-of-file"
# define MS_WHERE "%s: %s (wanted `%s')\n"

int		ms_here_tomstr(char **str, size_t len_rem, t_dlist *doc);
int		ms_here_read(char *delimiter, t_dlist **doc);

#endif