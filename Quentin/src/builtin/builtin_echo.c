/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 13:18:35 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	ft_bin_echo(int fd, char *str, int opt_n)
{
	write(fd, str, ft_strlen(str));
	if (opt_n)
		write(fd, "\n", 1);
	ft_bin_exit_status(0);
}
