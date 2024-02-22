/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:17 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/21 14:40:59 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_utils.h"
#include "../includes/parser.h"

void	ms_token_error(void *arg, int errnum, int fd_error)
{
	if (errno == errnum)
		return (perror(MS_TOKEN_ESOURCE));
	ft_putstr_fd(MS_TOKEN_ESOURCE, fd_error);
	ft_putstr_fd(": ", fd_error);
	if (MS_ETOKEN == errnum)
	{
		ft_putstr_fd(MS_ETOKEN_MSG, fd_error);
		ft_putstr_fd(" `", fd_error);
		ft_putchar_fd(*((char *)arg), fd_error);
		ft_putstr_fd("'", fd_error);
	}
	else if (MS_EQUOTE == errnum)
	{
		ft_putstr_fd(MS_EQUOTE_MSG, fd_error);
		ft_putstr_fd(":", fd_error);
		ft_putchar_fd(*((char *)arg), fd_error);
	}
	ft_putstr_fd("\n", fd_error);
}

int	ms_token_add_word(\
	t_dlist **tokens, char **input, int *quote)
{
	size_t	size_word;
	char	*word;
	t_token	*content;
	t_dlist	*new;

	size_word = 0;
	while ((*input)[size_word] && \
		NULL == ms_token_strchr(MS_METACHAR, (*input)[size_word], quote))
		size_word++;
	content = (t_token *)malloc(sizeof(t_token));
	if (NULL == content)
		return (ms_token_error(NULL, errno, 2), 1);
	content->operator = -1;
	word = (char *)malloc(sizeof(char) * (size_word + 1));
	if (NULL == word)
		return (free(content), ms_token_error(NULL, errno, 2), 1);
	ft_strlcpy(word, *input, size_word + 1);
	*input += size_word;
	content->word = word;
	new = ms_dlstnew(content, -1);
	if (NULL == new)
		return (free(word), free(content), \
			ms_token_error(NULL, errno, 2), -1);
	return (ms_dlstadd_back(tokens, new), 0);
}

int	ms_token_add_operator(\
	t_dlist **tokens, char **input, void *data)
{
	int		op_num;
	t_token	*content;
	t_dlist	*new;

	op_num = ms_token_get_operator(input, data);
	if (-1 == op_num)
		return (ms_token_error(*input, MS_ETOKEN, 2), 1);
	content = (t_token *)malloc(sizeof(t_token));
	if (NULL == content)
		return (ms_token_error(NULL, errno, 2), 1);
	content->operator = op_num;
	content->word = NULL;
	new = ms_dlstnew(content, -1);
	if (NULL == new)
		return (free(content), ms_token_error(NULL, errno, 2), 1);
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
	const char	**operator_array = ms_token_get_operator_arr(data);

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
