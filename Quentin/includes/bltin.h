/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/02 14:42:49 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_H
# define BLTIN_H

typedef int	(*t_builtin)(char **, char **, void *);

int	ms_bltin_echo(char **av, char **env, void *data);
int	ms_bltin_pwd(char **env, void *data);

#endif