/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:54 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 17:15:52 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "here.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*ms_xtoa(long long int num)
{
	int		n;
	int		m;
	char 	*base;
	char	*dest;
	
	base = "0123456789abcdef";	
	n = num;
	m = 0;
	while (n > 0)
	{
		n = n / 16;
		m++;
	}
	dest = malloc((m + 1) * sizeof(char));
	dest[m] = '\0';
	while (m > 0)
	{
		dest[--m] = base[(num % 16)];
		num = num / 16;
	}
	return (dest);
}

/*replaces << with < and delimiterwith tmp file location*/
static t_dlist	*ms_parse_here_replace(t_dlist *token)
{
	int 	here_fd;
	t_dlist	*list;
	char	*tmp;
	char	*tmp2;
	
	tmp = NULL;
	list = token;
	list = list->next;
	tmp2 = ms_xtoa((long long int)&list);
	tmp = ft_strjoin(MS_HERE_PATH, tmp2);
	here_fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (-1== here_fd)
		return (perror("here_doc"), errno = 0, token);
	if (0 != ms_here(here_fd, list->content))
		return (free(tmp), token);
	free(list->content);
	list->content = ft_strdup(tmp);
	close (here_fd);
	free(tmp);
	return (token);	
}
/*check if there is a here_doc, and deals with it*/
int	ms_parse_here(t_dlist *token)
{
	t_dlist	*list;

	list = token;
	while (NULL != list)
	{
		if (MS_TOKEN_HERE_DOC == list->type)
		{
			list->type = MS_TOKEN_INTPUT;
			list = ms_parse_here_replace(list);
		}
		list = list->next;
	}
	return (0);
}