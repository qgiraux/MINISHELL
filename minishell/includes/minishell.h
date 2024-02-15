/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:52 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/15 15:00:33 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

typedef struct s_elements
{
	int					operation;			
	char				*element;
	int					result;
}				t_elements;

t_list		*parser(char *input);
int			skip_quotes(char *input, int i);
int			separator(char *input, int i);
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_list		*add_element(t_list *element);
void		free_list(t_list *first);

#endif