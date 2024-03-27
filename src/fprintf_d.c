/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/25 14:29:06 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fprintf.h"
#include "fprintf_utils.h"

static void	_rev(char *str)
{
	const size_t	len = ft_strlen(str);
	const size_t	i_max = len / 2;
	char			tmp;
	size_t			i;

	if (NULL == str)
		return ;
	i = 0;
	while (i < i_max)
	{
		tmp = str[len - i - 1];
		str[len - i - 1] = str[i];
		str[i] = tmp;
		i++;
	}
}

static void	_fillbuff(long n, char *buff_num)
{
	size_t	i_n;
	int		isneg;

	i_n = 0;
	isneg = (n < 0);
	if (isneg)
		n = -n;
	while (n >= 10)
	{
		buff_num[i_n++] = '0' + n % 10;
		n /= 10;
	}
	buff_num[i_n++] = '0' + n % 10;
	if (isneg)
		buff_num[i_n++] = '-';
	buff_num[i_n++] = '\0';
}

void	ms_fprintf_d(char **format, size_t *i, char *buff, t_csd *args)
{
	char	s[12];
	size_t	i_s;

	*format += 2;
	if (NULL == args->d)
		return ;
	_fillbuff(*(args->d), s);
	_rev(s);
	i_s = 0;
	while (s[i_s] && *i < MS_BUFF_LEN)
		buff[(*i)++] = s[i_s++];
	args->d += 1;
}
