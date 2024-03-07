/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:40:52 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/06 14:01:05 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include "token.h"
# include "parser.h"

void	free_input(t_dlist *list);

# ifndef LIBFT_H
#  error Libft not found
# endif

#endif
