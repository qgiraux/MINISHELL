/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:52 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 18:08:12 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include "token.h"
# include "parser.h"

void 	free_input(t_dlist *list);
void 	print_input(t_dlist *list, const char **data);

# ifndef LIBFT_H
#  error Libft not found
# endif

#endif



