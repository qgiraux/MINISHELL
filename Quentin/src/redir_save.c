/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:15:21 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "redir_utils.h"

static int	ms_dlist_sep_redir(t_dlist **head, t_dlist **curr, t_dlist **redir)
{
	t_dlist	*prev;
	t_dlist	*next;

	if ((NULL == (*curr)->next) || (MS_TOKEN_WORD != (*curr)->next->type))
		return (ms_redir_error((void *)__FILE__, MS_EREDIR, 2, NULL), 1);
	if (NULL != *redir)
		ms_dlstclear(redir);
	prev = (*curr)->prev;
	if (NULL == (*curr)->next->next)
		next = NULL;
	else
		next = (*curr)->next->next;
	if (NULL != prev)
		prev->next = next;
	if (NULL != next)
		next->prev = prev;
	*redir = *curr;
	(*redir)->prev = NULL;
	(*redir)->next->next = NULL;
	*curr = next;
	if (NULL == prev)
		*head = next;
	return (0);
}

static int	ms_redir_dlist_open(t_dlist **r, void *data)
{
	int		fid_in;
	int		fid_out;
	char	*pathname;
	int		errnum;

	errnum = MS_EREDIR;
	ms_redir_data_get(&fid_in, &fid_out, data);
	if (NULL == *r || NULL == (*r)->next || NULL != (*r)->next->next)
		pathname = NULL;
	else
		pathname = (*r)->next->content;
	if (NULL == pathname || '\0' == *pathname)
		return (1); //ambiguous
	else if (MS_TOKEN_INTPUT == (*r)->type)
		errnum = ms_redir_file_in(&fid_in, data, pathname);
	else if (MS_TOKEN_OUTPUT == (*r)->type)
		errnum = ms_redir_file_out(&fid_out, data, pathname, 0);
	else if (MS_TOKEN_APPEND == (*r)->type)
		errnum = ms_redir_file_out(&fid_in, data, pathname, 1);
	else if (MS_TOKEN_HERE_DOC == (*r)->type)
		errnum = ms_redir_file_here(&fid_in, data, pathname);
	ms_dlstclear(r);
	if (MS_EREDIR == errnum)
		return (ms_redir_error((void *)__FILE__, MS_EREDIR, 2, NULL), 1);
	return (0);
}

int	ms_redir_save(t_dlist **list, void *data)
{
	t_dlist	*curr;
	t_dlist	*redir;

	redir = NULL;
	curr = *list;
	while (curr)
	{
		if (ms_dlist_istype_redir(curr))
		{
			if (ms_dlist_sep_redir(list, &curr, &redir))
				return (1);
			if (ms_exp(&redir, data))
				return (1);
			if (ms_redir_dlist_open(&redir, data))
				return (1);
		}
		else
			curr = curr->next;
	}
	return (0);
}
