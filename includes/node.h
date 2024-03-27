/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:04:57 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/13 13:17:21 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "dlist.h"
# include <sys/types.h>
# include <sys/wait.h>
# include "parser.h"
# include "token.h"

typedef struct s_pipe
{
	int		count;
	int		*pid;
	int		**pipefd;
	int		*status;
}			t_pipe;

typedef struct s_fork
{
	int		pid;
	int		stat;
	int		rpid;
}			t_fork;

int		ms_node_list(t_dlist *node, int status, void *data);
int		ms_node(t_dlist *node, int status, void *data);
int		ms_node_compound(t_dlist *node, int status, void *data);
int		ms_node_pipe(t_dlist *node, int status, void *data);
void	ms_free_p(t_pipe p, int nb_pipe);
void	ms_free_all_p(t_pipe p, int nb_pipe);
t_pipe	ms_init_pipe(int nb_pipe);

#endif
