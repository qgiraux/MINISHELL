/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:57 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/01 16:41:29 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_TYPE_H
# define NODE_TYPE_H

# include "dlist.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipe
{
	int		i;
	int		*pid;
	int		**pipefd;
	int		*status;
}			t_pipe;

int	node_type_list(t_dlist *node, int status, const char **data);
int	node_type(t_dlist *node, int status, const char **data);
int	node_type_compound(t_dlist *node, int status, const char **data);
int	node_type_cmd(t_dlist *node, const char **data);
int	node_type_pipe(t_dlist *node, int status, const char **data);

#endif
