/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/22 13:28:09 by jerperez         ###   ########.fr       */
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
	int				type;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}		t_dlist;

t_dlist		*ms_dlstnew(void *content, int type);
void		ms_dlstadd_back(t_dlist **lst, t_dlist *new);
void		ms_dlstclear(t_dlist **lst);
void		ms_dlstcut(t_dlist *cut);
t_dlist		*ms_dlstfirst(t_dlist *lst);
t_dlist		*ms_dlstlast(t_dlist *lst);
//
int			ms_dlist_istype_word(t_dlist *list);
int			ms_dlist_istype_word_only(t_dlist *list);
int			ms_dlist_istype_redir(t_dlist *list);
int			ms_dlist_istype_token(t_dlist *list);
int			ms_dlist_istype_operator(t_dlist *list);

#endif
