/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:19:34 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/19 10:55:42 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	n;

	n = 0;
	dest = (char *) malloc((len + 1) * sizeof (char));
	if (!dest)
		return (NULL);
	while (n < len && s[start + n])
	{
		dest[n] = s[start + n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	n;
	char	*s;

	s = (char *)str;
	n = 0;
	c = c % 256;
	while (n <= ft_strlen(s))
	{
		if (str[n] == c)
			return (s + n);
		n++;
	}
	return (NULL);
}

#define BUFFER_SIZE 1

static char	*fill_line(char *stock, char *buffer, int fd)
{
	ssize_t	readsize;
	char	*tmp;

	readsize = 1;
	while (readsize > 0)
	{
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize < 0)
		{
			if (stock)
				free(stock);
			return (NULL);
		}
		if (readsize == 0)
			return (stock);
		buffer[readsize] = 0;
		if (!stock)
			stock = ft_strdup("");
		tmp = stock;
		stock = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			return (stock);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stock;

	buffer = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (BUFFER_SIZE <= 0 || fd < 0 || (read(fd, 0, 0) < 0))
	{
		free (stock);
		stock = NULL;
		free (buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line(stock, buffer, fd);
	free (buffer);
	buffer = NULL;
	if (!line || line[0] == 0 || line == NULL)
	{
		free (stock);
		stock = NULL;
		return (NULL);
	}
	return (line);
}
