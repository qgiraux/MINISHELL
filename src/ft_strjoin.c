/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:16 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/16 15:34:28 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*suite(char const *s1, char const *s2)
{
	int		n;
	int		m;
	char	*dest;

	m = 0;
	n = 0;
	dest = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[n])
	{
		dest[n] = s1[n];
		n++;
	}
	while (s2[m])
	{
		dest[n + m] = s2[m];
		m++;
	}
	dest[n + m] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		dest = (char *) malloc (1 * sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = 0;
		return (dest);
	}
	return (suite(s1, s2));
}
