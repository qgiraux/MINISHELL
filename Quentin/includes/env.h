/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:48:23 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/08 13:19:38 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*ms_env_get_line(const char **env, const char *var);
char		*ms_env_mget_str(const char **env, const char *var, char **value);
char		**ms_env(void *data);

#endif
