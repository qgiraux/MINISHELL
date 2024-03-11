/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 13:55:40 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_H
# define BLTIN_H

typedef int	(*t_builtin)(char **, void *);

int	ms_bltin_echo(char **av, void *data);
int	ms_bltin_pwd(char **av, void *data);

#endif