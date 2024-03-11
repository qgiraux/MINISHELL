/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:58:56 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:40:11 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "redir_utils.h"

static int	ms_dlist_sep_redir(t_dlist **head, t_dlist **curr, t_dlist **redir)
{
	t_dlist	*prev;
	t_dlist	*next;

	if ((NULL == (*curr)->next) || (MS_TOKEN_WORD != (*curr)->next->type))
		return (ms_e(__FILE__, __LINE__, 1), 1);
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
	return (MS_SUCCESS);
}

static int	ms_redir_save_open(int type, char *pathname, void *data)
{
	int		fid_in;
	int		fid_out;

	ms_redir_data_get(&fid_in, &fid_out, data);
	if (MS_TOKEN_INTPUT == type)
		return (ms_redir_file_in(&fid_in, data, pathname));
	else if (MS_TOKEN_OUTPUT == type)
		return (ms_redir_file_out(&fid_out, data, pathname, 0));
	else if (MS_TOKEN_APPEND == type)
		return (ms_redir_file_out(&fid_in, data, pathname, 1));
	else if (MS_TOKEN_HERE_DOC == type)
		return (ms_redir_file_here(&fid_in, data, pathname));
	else
		return (ms_e(__FILE__, __LINE__, 1), 1);
	return (MS_SUCCESS);
}

static int	ms_redir_save_check(t_dlist *r, char *pattern)
{
	if (NULL == r || NULL == r->next || NULL != r->next->next)
		return (ms_redir_error(pattern, EREDIR_BADWORD), 1);
	if (NULL == r->next->content || '\0' == ((char *)r->next->content)[0])
		return (ms_redir_error(pattern, EREDIR_BADWORD), 1);
	return (MS_SUCCESS);
}

static int	ms_redir_save_exp(t_dlist **ptr_redir, void *data)
{
	char	*str_unexp;
	t_dlist	*new;

	str_unexp = (char *)((*ptr_redir)->next->content);
	free((*ptr_redir)->next);
	(*ptr_redir)->next = NULL;
	new = NULL;
	if (ms_exp_str((const char *)str_unexp, &new, data))
		return (ms_e(__FILE__, __LINE__, 0), free(str_unexp), 1);
	(*ptr_redir)->next = new;
	if (ms_redir_save_check((*ptr_redir), str_unexp))
		return (ms_e(__FILE__, __LINE__, 0), free(str_unexp), 1);
	if (ms_redir_save_open(\
			(*ptr_redir)->type, (char *)((*ptr_redir)->next->content), data))
		return (ms_e(__FILE__, __LINE__, 0), free(str_unexp), 1);
	return (free(str_unexp), MS_SUCCESS);
}

/* ms_redir_save:
 * Gets unexpanded tokens and opens redirection files on the go
 * Redirection tokens are isolated and expanded before expansion
 * Returns an error - if the expansion fails
 * - if the expansion succeeds but results in "" target or mutliple targets
 */

int	ms_redir_save(t_dlist **tokens, void *data)
{
	t_dlist	*curr;
	t_dlist	*redir;

	redir = NULL;
	curr = *tokens;
	while (curr)
	{
		if (ms_dlist_istype_redir(curr))
		{
			if (ms_dlist_sep_redir(tokens, &curr, &redir))
				return (ms_e(__FILE__, __LINE__, 0), 1);
			if (ms_redir_save_exp(&redir, data))
				return (ms_e(__FILE__, __LINE__, 0), \
					ms_dlstclear(&redir), 1);
			ms_dlstclear(&redir);
		}
		else
			curr = curr->next;
	}
	return (MS_SUCCESS);
}
