/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 14:42:53 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_UTILS_H
# define HERE_UTILS_H

# include "libft.h"
# include "dlist.h"
# include <unistd.h>
# include <errno.h>

# define READ_BUFF_LEN 100
# define MS_WEOF 500
# define MS_HERE_LINE "> "

int	ms_here_tostr(char **str, size_t len_rem, t_dlist *doc);
int	ms_here_read(char *delimiter, t_dlist **doc);

#endif