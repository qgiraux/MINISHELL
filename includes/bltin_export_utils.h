/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:07:28 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/26 11:17:55 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_EXPORT_UTILS_H
# define BLTIN_EXPORT_UTILS_H

int		ms_is_variable(char *s);
char	*ms_mget_variable(char *str);
int		ms_data_env_add_line(void *data \
		, char **env, char *variable, char *new_line);
int		ms_data_env_replace_line(char **env, \
		char *variable, char *new_line);
#endif