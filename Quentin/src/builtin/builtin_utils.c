/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:41:08 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 15:15:21 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"
# include <string.h>
# include <stdlib.h>

char	*ft_getenv(const char *name)
{
	return (getenv(name));
}

void	ft_error(char *bin, int errnum, int fd_error)
{
	ft_putstr_fd(bin, fd_error);
	ft_putstr_fd(": ", fd_error);
	ft_putstr_fd(strerror(errnum), fd_error);
	ft_putstr_fd("\n", fd_error);
}

void	ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((unsigned char *)s + i++) = (unsigned char)c;
}

char	*ft_strncat(char *dest, char *src, size_t n)
{
	const size_t	dest_len = ft_strlen(dest);
	size_t			i;

	i = 0;
	while (*src && i < n)
		dest[dest_len + i++] = *src++;
	dest[dest_len + i] = '\0';
	return (dest);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_bin_exit_status(int status)
{
	status = status % 256;
	return ;
}

void	ft_putstr_fd(char *str, int fd)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
}
