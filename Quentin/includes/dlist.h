/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/21 12:02:50 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_dlist
{
	void			*content;
	int				type; //cmd / pipe / cmp / token / list
	struct s_dlist	*next;
	struct s_dlist	*prev;
}		t_dlist;

t_dlist		*ms_dlstnew(void *content, int type);
void		ms_dlstadd_back(t_dlist **lst, t_dlist *new);
void		ms_dlstclear(t_dlist **lst, void (*del)(void *));
void		ms_dlstcut(t_dlist *cut);
t_dlist		*ms_dlstfirst(t_dlist *lst);
t_dlist		*ms_dlstlast(t_dlist *lst);

#endif
