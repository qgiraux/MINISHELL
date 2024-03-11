/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/08 13:52:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"

static char	*ms_exp_escape_replace(char *str, char *new, char *list)
{
	size_t	i_str;
	size_t	i_new;

	i_str = 0;
	i_new = 0;
	while ('\0' != str[i_str])
	{
		if (NULL == ft_strchr(list, str[i_str]))
			new[i_new++] = str[i_str];
		else
		{
			new[i_new++] = EXP_ESC;
			new[i_new++] = str[i_str];
		}
		i_str++;
	}
	new[i_new] = '\0';
	free(str);
	return (new);
}

static void	ms_exp_escape_removal_write(char *str, char *new, char *list)
{
	size_t	i_str;
	size_t	i_new;

	i_str = 0;
	i_new = 0;
	while ('\0' != str[i_str])
	{
		if (EXP_ESC == str[i_str])
			new[i_new++] = str[++i_str];
		else if (NULL != ft_strchr(list, str[i_str]))
			;
		else
			new[i_new++] = str[i_str];
		i_str++;
	}
	new[i_new] = '\0';
}

char	*ms_exp_escape(char *str, char *to_escape)
{
	char	*str_esc;
	size_t	n_esc;
	size_t	len_str;

	n_esc = 0;
	len_str = 0;
	while ('\0' != str[len_str])
	{
		if (NULL != ft_strchr(to_escape, str[len_str]))
			n_esc++;
		len_str++;
	}
	if (0 == n_esc)
		return (str);
	str_esc = (char *)malloc(sizeof(char) * (len_str + n_esc + 1));
	if (NULL == str_esc)
		return (ms_perror(MS_E), NULL);
	return (ms_exp_escape_replace(str, str_esc, to_escape));
}

char	*ms_exp_escape_removal(char *str, char *lst)
{
	char	*new;
	size_t	n_rem;
	size_t	len_str;

	n_rem = 0;
	len_str = 0;
	while ('\0' != str[len_str])
	{
		if (EXP_ESC == str[len_str])
		{
			n_rem++;
			len_str++;
		}
		else if (NULL != ft_strchr(lst, str[len_str]))
			n_rem++;
		len_str++;
	}
	if (0 == n_rem)
		return (str);
	new = (char *)malloc(sizeof(char) * (len_str - n_rem + 1));
	if (NULL == new)
		return (perror(MS_E), NULL);
	ms_exp_escape_removal_write(str, new, lst);
	return (free(str), new);
}


// int main(int ac, char **av)
// {
// 	char	*un_esc;
// 	char	*esc;
// 	char	*in;
// 	if (2 != ac)
// 		return (1);
// 	in = ft_strdup(av[1]);
// 	printf("av=%s", in);
// 	esc = ms_exp_escape(in, EXP_ESC_LIST);
// 	printf("\tesc=%s", esc);
// 	un_esc = ms_exp_escape_removal(esc, EXP_ESC_LIST);
// 	printf("\tun_esc=%s\n", un_esc);
// 	return (0);
// }
