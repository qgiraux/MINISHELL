/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:54 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 17:07:26 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "here.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*replaces << with < and delimiterwith tmp file location*/
static t_dlist	*ms_parse_here_replace(t_dlist *token)
{
	int 	here_fd;
	t_dlist	*list;

	list = token;
	list->type = MS_TOKEN_INTPUT;
	list = list->next;
	here_fd = open(MS_HERE_PATH, O_CREAT | O_TRUNC | O_RDWR, O_WRONLY);
	if (-1== here_fd)
		return (perror("here_doc"), errno = 0, token);
	ms_here(here_fd, list->content);
	free(list->content);
	list->content = malloc(ft_strlen(MS_HERE_PATH) * sizeof(char));
	ft_strlcpy(list->content, MS_HERE_PATH, ft_strlen(MS_HERE_PATH));
	close (here_fd);
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
			list = ms_parse_here_replace(list);
			if (ft_strlen(MS_HERE_PATH) != ft_strlen(list->content))
				return (write(2, "error when handling here_doc\n", 29), -1);
		}
		list = list->next;
	}
	return (0);
}