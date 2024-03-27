/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/23 11:00:10 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPRINTF_H
# define FPRINTF_H

typedef struct s_csd
{
	char	*c;
	char	**s;
	int		*d;
}		t_csd;

void	ms_fprintf_args(\
	const char *c, const char **s, const int *d, t_csd *args);
int		ms_fprintf(int fd, char *format, t_csd *args);

#endif