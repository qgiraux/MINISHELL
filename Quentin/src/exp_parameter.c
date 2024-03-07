/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/06 11:31:32 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"

static int	ms_exp_parameter_list_add(\
	t_dlist **values, char *big, size_t len_str, int type)
{
	char	*str;
	t_dlist	*new;

	if (0 == len_str)
		str = NULL;
	else
	{
		str = (char *)malloc(sizeof(char) * (len_str + 1));
		if (NULL == str)
			return (1);
		ft_strlcpy(str, big, len_str + 1);
	}
	new = ms_dlstnew(str, type);
	if (NULL == new)
	{
		if (NULL != str)
			free(str);
		return (1);
	}
	ms_dlstadd_back(values, new);
	return (0);
}

static void	ms_exp_parameter_listtostr_write(t_dlist *values, char *str)
{
	char	*content;

	while (values)
	{
		content = (char *)(values->content);
		while (*content)
			*str++ = *content++;
		values = values->next;
	}
	*str = '\0';
}

static char	*ms_exp_parameter_listtostr(t_dlist *values)
{
	size_t	len;
	t_dlist	*curr;
	char	*str;

	curr = values;
	len = 0;
	while (curr)
	{
		len += ft_strlen((char *)curr->content);
		curr = curr->next;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == str)
		return (NULL);
	ms_exp_parameter_listtostr_write(values, str);
	return (str);
}

t_dlist	*ms_exp_parameter_list(char *input, char **env, void *data)
{
	t_dlist	*values;
	size_t	i_in;
	size_t	len;
	int		type;

	(void)env;
	(void)data;
	values = NULL;
	i_in = 0;
	while ('\0' != input[i_in])
	{
		len = 0;
		ms_parameter_quote(input + i_in, &len, &type);
		if (0 == len)
			ms_parameter_var(input + i_in, &len, &type);
		if ('\0' != input[i_in] && 0 == len)
			return (NULL); //
		if (ms_exp_parameter_list_add(&values, input + i_in, len, type))
			return (NULL); //
		i_in += len;
	}
	return (values);
}

char	*ms_exp_parameter(char *input, char **env, void *data)
{
	t_dlist	*values;
	t_dlist	*curr;

	values = ms_exp_parameter_list(input, env, data);
	if (NULL == values)
		return (NULL);
	curr = values;
	while (curr)
	{
		ms_exp_parameter_replace(curr, env, data);
		curr = curr->next;
	}
	return (ms_exp_parameter_listtostr(values));
}

// #include "env.h"
// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	char	*input = "ok$AA'lol'";
// 	char	*exp;
// 	char	**env;

// 	(void)ac;
// 	(void)av;
// 	env = ms_env(NULL);
// 	printf("input:%s\n", input);
// 	exp = ms_exp_parameter(input, env, NULL);
// 	printf("exp:%s\n", exp);
// 	return (0);
// }
