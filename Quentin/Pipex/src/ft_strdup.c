/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:04:19 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/16 18:07:06 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strdup(const char *str)
{
	int		n;
	char	*dest;

	dest = (char *) malloc (ft_strlen(str) + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	n = 0;
	while (str[n])
	{
		dest[n] = str[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}
