/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/20 14:19:56 by jerperez         ###   ########.fr       */
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
	struct s_dlist	*next;
	struct s_dlist	*prev;
}		t_dlist;

t_dlist		*ms_dlstnew(void *content);
void		ms_dlstadd_back(t_dlist **lst, t_dlist *new);
void		ms_dlstclear(t_dlist **lst, void (*del)(void *));
void		ms_dlstcut(t_dlist *cut);
t_dlist		*ms_dlstfirst(t_dlist *lst);
t_dlist		*ms_dlstlast(t_dlist *lst);

#endif
