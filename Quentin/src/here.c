/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:39:34 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here.h"
#include "here_utils.h"

/* ms_here_tmp_remove:
 * must be called before programm ends and after ms_here is called
 * delete tmp file
 * can be called anytime
 */

void	ms_here_tmp_remove(void)
{
	int	errnum;

	errnum = errno;
	unlink(MS_HERE_PATH);
	errno = errnum;
}

/* ms_here:
 * here doc
 * writes in file descripter <fd_doc> EOF is <delimiter>
 * here doc read ends iff:
 * error OR a line has the exact value of <delimiter> OR ctrl+D on an empty line
 */

int	ms_here(int fd_doc, char *delimiter)
{
	t_dlist	*doc;
	int		errnum;
	char	*str;
	size_t	len;

	if (-1 == fd_doc || NULL == delimiter || '\0' == *delimiter)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	doc = NULL;
	errnum = ms_here_read(delimiter, &doc);
	if (MS_WEOF == errnum)
		len = 0;
	else if (errnum)
		return (ms_e(__FILE__, __LINE__, 0), 1);
	else
		len = ft_strlen(delimiter);
	if (ms_here_tomstr(&str, len, doc))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	ft_putstr_fd(str, fd_doc);
	return (free(str), MS_SUCCESS);
}

// // // // //

// int main(int ac, char **av)
// {
// 	int	fd = 1;

// 	if (2 != ac)
// 		return (1);
// 	printf("delimiter:%s\n", av[1]);
// 	ms_here(fd, av[1]);
// 	return (0);
// }
