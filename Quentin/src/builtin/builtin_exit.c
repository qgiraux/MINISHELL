/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:40:55 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 13:40:24 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

void	ft_bin_exit(int *ptr_status)
{
	int	status;

	if (NULL == status)
		status = 0;
	else
		status = *ptr_status;
	ft_bin_exit_status(status);
	exit(status);
}
