/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/15 15:10:19 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_H
# define BLTIN_H

typedef int	(*t_builtin)(char **, void *);

int	ms_bltin_echo(char **av, void *data);
int	ms_bltin_pwd(char **av, void *data);
int	ms_bltin_export(char **av, void *data);
int	ms_bltin_cd(char **av, void *data);
int	ms_bltin_env(char **av, void *data);
int	ms_bltin_unset(char **av, void *data);
int	ms_bltin_exit(char **av, void *data);

#endif