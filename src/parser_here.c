/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:00:54 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 10:10:03 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "here.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "error.h"

static void	ms_mxtoa(long long int n, char *buff, char *base, int nbase)
{
	size_t			i;

	i = 0;
	while (n >= nbase)
	{
		buff[i++] = base[n % nbase];
		n /= nbase;
	}
	buff[i++] = base[n % nbase];
	buff[i] = '\0';
}

/*replaces << with < and delimiterwith tmp file location*/
static int	ms_parse_here_replace(t_dlist *token)
{
	char	file_id[18];
	int		here_fd;
	t_dlist	*list;
	char	*file_name;

	file_name = NULL;
	list = token->next;
	ms_mxtoa((long long int)list, file_id, "0123456789abcdef", 16);
	file_name = ft_strjoin(MS_HERE_PATH, file_id);
	if (NULL == file_name)
		return (1);
	here_fd = open(file_name, \
		O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == here_fd)
		return (free(file_name), ms_perror(MS_E), 1);
	if (0 != ms_here(here_fd, list->content))
		return (free(file_name), ms_e(__FILE__, __LINE__, 0), 1);
	close(here_fd);
	free(list->content);
	list->content = file_name;
	return (MS_SUCCESS);
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
			if (ms_parse_here_replace(list))
				return (1);
		}
		list = list->next;
	}
	return (MS_SUCCESS);
}
