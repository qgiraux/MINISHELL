/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:17 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/22 17:20:16 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_utils.h"
#include "data.h"
#include "fprintf.h"

void	ms_token_error(char chr, int errnum, int fd_error)
{
	t_csd		fprintf_args;
	const char	*s[2] = {MS_E, NULL};
	const char	c[2] = {chr, '\0'};

	ms_fprintf_args(c, s, NULL, &fprintf_args);
	if (MS_ETOKEN == errnum)
		ms_fprintf(fd_error, MS_ETOKEN_MSGC, &fprintf_args);
	else if (MS_EQUOTE == errnum)
		ms_fprintf(fd_error, MS_EQUOTE_MSG, &fprintf_args);
}

int	ms_token_add_word(\
	t_dlist **tokens, char **input, int *quote)
{
	size_t	size_word;
	char	*word;
	t_dlist	*new;

	size_word = 0;
	while ((*input)[size_word] && \
		NULL == ms_token_strchr(MS_METACHAR, (*input)[size_word], quote))
		size_word++;
	word = (char *)malloc(sizeof(char) * (size_word + 1));
	if (NULL == word)
		return (ms_perror(MS_E), 1);
	ft_strlcpy(word, *input, size_word + 1);
	new = ms_dlstnew(word, MS_TOKEN_WORD);
	if (NULL == new)
		return (free(word), ms_perror(MS_E), 1);
	*input += size_word;
	return (ms_dlstadd_back(tokens, new), 0);
}

int	ms_token_add_operator(\
	t_dlist **tokens, char **input, void *data)
{
	int		op_num;
	t_dlist	*new;

	op_num = ms_token_get_operator(input, data);
	if (-1 == op_num)
		return (ms_token_error(**input, MS_ETOKEN, 2), 1);
	new = ms_dlstnew(NULL, op_num);
	if (NULL == new)
		return (ms_perror(MS_E), 1);
	ms_dlstadd_back(tokens, new);
	return (0);
}

char	*ms_token_strchr(const char *s, int c, int *quote)
{
	if (quote && (MS_QUOTE_1 == c || MS_QUOTE_2 == c))
	{
		if (0 == *quote)
			*quote = c;
		else if (c == *quote)
			*quote = 0;
	}
	if (NULL == quote || 0 == *quote)
		return (ft_strchr(s, c));
	return (NULL);
}

int	ms_token_get_operator(char **input, void *data)
{
	size_t		len_op;
	int			op;
	size_t		i;
	int			n;
	const char	**operator_array = ms_data_operator_get(data);

	n = 0;
	len_op = 0;
	op = MS_TOKEN_WORD;
	while (operator_array[n])
	{
		i = 0;
		while (operator_array[n][i] && (*input)[i] == operator_array[n][i])
			i++;
		if (i > len_op && '\0' == operator_array[n][i])
		{
			if ((('\0' == (*input)[i]) \
				|| !ms_token_strchr(MS_METACHAR_NOT_BLANK, (*input)[i], NULL)))
				return (*input += i, n);
			op = n;
			len_op = i;
		}
		n++;
	}
	return (*input += len_op, op);
}
