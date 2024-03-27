/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_tostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:04:50 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_utils.h"

static int	_tostr_len(t_dlist *doc)
{
	size_t	len;
	size_t	i;
	char	*content;

	len = 0;
	while (doc)
	{
		content = (char *)(doc->content);
		i = 0;
		while (i < READ_BUFF_LEN && '\0' != content[i])
			i++;
		len += i;
		doc = doc->next;
	}
	return (len);
}

static void	_tostr_cpy(char *str, t_dlist *doc, size_t len)
{
	char	*content;
	size_t	i_str;
	size_t	i;

	i_str = 0;
	while (doc && i_str < len)
	{
		content = (char *)(doc->content);
		i = 0;
		while (i < READ_BUFF_LEN && '\0' != content[i] && i_str < len)
			str[i_str++] = content[i++];
		doc = doc->next;
	}
	str[i_str] = '\0';
}

int	ms_here_tomstr(char **str, size_t len_rem, t_dlist *doc)
{
	size_t	len;

	len = _tostr_len(doc) - len_rem;
	*str = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == *str)
		return (ms_perror(MS_E), ms_dlstclear(&doc), 1);
	_tostr_cpy(*str, doc, len);
	ms_dlstclear(&doc);
	return (MS_SUCCESS);
}
