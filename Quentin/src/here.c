/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 15:31:49 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here.h"
#include "here_utils.h"

void	ms_here_tmp_remove(void)
{
	unlink(MS_HERE_PATH);
	errno = 0;
}

int	ms_here(int fd_doc, char *delimiter)
{
	t_dlist	*doc;
	int		errnum;
	char	*str;
	size_t	len;

	if (-1 == fd_doc || NULL == delimiter || '\0' == *delimiter)
		return (1);
	errnum = ms_here_read(delimiter, &doc);
	if (MS_WEOF == errnum)
		len = 0;
	else if (errnum)
		return (1);
	else
		len = ft_strlen(delimiter);
	if (ms_here_tostr(&str, len, doc))
		return (1);
	ft_putstr_fd(str, fd_doc);
	return (0);
}

// // // //

// int main(int ac, char **av)
// {
// 	int	fd = 1;

// 	if (2 != ac)
// 		return (1);
// 	ms_here(fd, av[1]);
// 	return (0);
// }
