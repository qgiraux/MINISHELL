/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:36:21 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 14:37:02 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	ft_bin_pwd(void)
{
	const int	fd = 1;
	char		buff[BUFF_LEN];
	char		*cwd;

	ft_memset(buff, 0, BUFF_LEN);
	cwd = getcwd(buff, BUFF_LEN);
	if (NULL == cwd)
		; //
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	ft_bin_pwd();
// }
