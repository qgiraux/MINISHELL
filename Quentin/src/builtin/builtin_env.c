/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 13:04:31 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

extern char	**environ;

static char	**ft_bin_env_get(void)
{
	return (environ);
}

void	ft_bin_env(void)
{
	const int		fd = 1;
	const char		**env = (const char **)ft_bin_env_get();
	unsigned int	i;

	if (!env)
		return ;
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i++], fd);
		write(fd, "\n", 1);
	}
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	ft_bin_env();
// }
