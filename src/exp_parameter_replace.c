/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:26:01 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"
#include "env.h"
#include "data.h"

static int	_name(t_dlist *curr, char **env)
{
	char	*str;
	char	*escpd_content;

	if (NULL == curr->content)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	if (ms_env_mget_str((const char **)env, (char *)(curr->content) + 1, &str))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	if (NULL == str)
		escpd_content = ft_strdup("");
	else
		escpd_content = ms_exp_escape(str, EXP_ESC_LIST);
	if (NULL == escpd_content)
		return (ms_perror(MS_E), 1);
	free(curr->content);
	curr->content = escpd_content;
	curr->type = MS_PARA_STR;
	return (MS_SUCCESS);
}

static int	_spe0(t_dlist *curr, void *data)
{
	char	*str;
	char	*dup;

	str = ms_data_exit_pipe_get(data);
	if (NULL == str)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	dup = ft_strdup(str);
	if (NULL == str)
		return (ms_perror(MS_E), 1);
	if (curr->content)
		free(curr->content);
	curr->content = dup;
	curr->type = MS_PARA_CONST_STR;
	return (MS_SUCCESS);
}

int	ms_exp_parameter_replace(t_dlist *curr, char **env, void *data)
{
	if (MS_PARA_SPE0 == curr->type)
		return (_spe0(curr, data));
	else if (MS_PARA_NAME == curr->type)
		return (_name(curr, env));
	return (MS_SUCCESS);
}
