/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:46:07 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/11 18:39:17 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin_utils.h"
#include "env.h"
#include <unistd.h>

int	ms_bltin_cd(char **av, void *data)
{
	char	*path;
	int		check;
	
	if (!av[1])
		check = chdir(ms_env_mget_str((char **)data->env, "HOME", &path));
	else
		check = chdir(av[1]);
	if (-1 == check)
		write(2, "cd: no such path or directory\n", 26);
	return (0);	
}