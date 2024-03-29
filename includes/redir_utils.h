/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/29 14:50:28 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_UTILS_H
# define REDIR_UTILS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "dlist.h"
# include "token.h"
# include "redir.h"
# include "error.h"

# define EREDIR_BADWORD_MSG "%s: %s: ambiguous redirect\n"

typedef struct s_redir
{
	int	fid_in;
	int	fid_out;
}		t_redir;

int		ms_redir_file_out(int *fid, void *data, char *path, int append_mode);
int		ms_redir_file_in(int *fid, void *data, char *pathname);
int		ms_redir_file_here(int *fid, void *data, char *pathname);
void	ms_redir_error(char *arg);

#endif