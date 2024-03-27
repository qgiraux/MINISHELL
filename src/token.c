/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:53:27 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:34:12 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token_utils.h"

static t_dlist	*_list_return(t_dlist **token_list, int quote)
{
	if (quote)
	{
		ms_dlstclear(token_list);
		ms_token_error(quote, MS_EQUOTE, 2);
		return (NULL);
	}
	return (*token_list);
}

/* ms_token_list:
 * Creates token list from input line
 * The operators should be constants stored in data (see token.h)
 * Tokens are either Words or Operators
 * The list is malloc'ed and needs to be freed
 */
t_dlist	*ms_token_list(char *input, void *data)
{
	int		quote;
	t_dlist	*token_list;

	token_list = NULL;
	quote = 0;
	while (*input)
	{
		if (NULL == ms_token_strchr(MS_METACHAR, *input, NULL))
		{
			if (ms_token_add_word(&token_list, &input, &quote))
				return (ms_dlstclear(&token_list), NULL);
		}
		else
		{
			if (NULL == ft_strchr(MS_BLANK, *input))
			{
				if (ms_token_add_operator(&token_list, &input, data))
					return (ms_dlstclear(&token_list), NULL);
			}
			else
				input++;
		}
	}
	return (_list_return(&token_list, quote));
}
