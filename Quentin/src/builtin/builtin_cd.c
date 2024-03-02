/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:50:42 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 15:20:03 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin_pwd.h"
#include "bin.h"

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static void	ft_bin_cd_chdir(char *path)
{
	const int	fd_error = 2;

	if (-1 == chdir(path))
	{
		ft_error("cd", errno, fd_error);
		//
	}
	return ;
}

void	ft_bin_cd(char *operand)
{
	char	*str;

	if (NULL == operand)
	{
		str = ft_getenv(ENV_HOME);
		if (NULL != str && '\0' == *str)
			ft_bin_cd_chdir(str);
	}
	else
		ft_bin_cd_chdir(operand);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	// ft_bin_cd_abs("patate");
// 	// ft_bin_cd_rel("patate");
// 	ft_bin_pwd();
// 	if (2 == ac)
// 		ft_bin_cd(av[1]);
// 	else
// 		ft_bin_cd(NULL);
// 	ft_bin_pwd();
// }
