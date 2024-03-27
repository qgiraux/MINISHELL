/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:06:41 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_utils.h"

static int	_end(ssize_t *len, char *delimiter, char c, ssize_t n)
{
	if ('\0' == delimiter[*len])
	{
		if ('\n' == c)
		{
			(*len)++;
			return (-1);
		}
		*len = -1;
		return (n);
	}
	else if (delimiter[*len] == c)
		(*len)++;
	else
		*len = -1;
	return (0);
}

static int	_len(\
	ssize_t	*len, char *delimiter, char *buff, ssize_t n)
{
	ssize_t	i;
	int		i_end;

	i = 0;
	while (i < n && buff[i])
	{
		if (-1 == *len)
		{
			if ('\n' == buff[i])
				(*len) = 0;
		}
		else
		{
			i_end = _end(len, delimiter, buff[i], n);
			if (-1 == i_end)
				return (i);
			else if (i_end)
				return (i_end);
		}
		i++;
	}
	return (n);
}

static int	_madd(t_dlist **doc, char *buff, ssize_t n)
{
	char			*str;
	t_dlist			*new;

	if (0 == n)
		return (MS_SUCCESS);
	else
		str = (char *)malloc(sizeof(char) * (n + 1));
	if (NULL == str)
		return (ms_perror(MS_E), 1);
	if (READ_BUFF_LEN != n)
	{
		str[n - 1] = '\0';
		str[n] = '\0';
	}
	else
		str[n] = '\0';
	ft_memcpy(str, buff, n);
	new = ms_dlstnew(str, -1);
	if (NULL == new)
		return (ms_perror(MS_E), free(str), 1);
	ms_dlstadd_back(doc, new);
	return (MS_SUCCESS);
}

static void	_prompt(ssize_t *len, int *put_line)
{
	if (*put_line)
	{
		ft_putstr_fd(MS_HERE_LINE, STDOUT_FILENO);
		*put_line = 0;
		*len = 0;
	}
}

int	ms_here_read(char *delimiter, t_dlist **doc)
{
	const int		len_eof = ft_strlen(delimiter) + 1;
	char			buff[READ_BUFF_LEN];
	ssize_t			bread;
	ssize_t			len;
	int				put_line;

	put_line = 1;
	len = -1;
	while (len != len_eof)
	{
		_prompt(&len, &put_line);
		bread = read(STDIN_FILENO, buff, READ_BUFF_LEN);
		if (-1 == bread)
			return (ms_perror(MS_E), 1);
		if (0 == len && 0 == bread)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (MS_WEOF);
		}
		put_line = ('\n' == buff[bread - 1]);
		bread = _len(&len, delimiter, buff, bread);
		if (_madd(doc, buff, bread))
			return (ms_e(__FILE__, __LINE__, 0), 1);
	}
	return (MS_SUCCESS);
}
