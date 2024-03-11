/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:39:11 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"
#include "env.h"

static char	*ms_data_get_pipeline_exit(void *data)
{
	return ((char *)data); //WIP
}

static int	ms_exp_parameter_replace_name(t_dlist *curr, char **env, void *data)
{
	char	*str;
	char	*escpd_content;

	(void)data;
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

static int	ms_exp_parameter_replace_spe0(t_dlist *curr, char **env, void *data)
{
	char	*str;

	(void)env;
	str = ms_data_get_pipeline_exit(data);
	if (curr->content)
		free(curr->content);
	curr->content = str;
	curr->type = MS_PARA_CONST_STR;
	return (0);
}

int	ms_exp_parameter_replace(t_dlist *curr, char **env, void *data)
{
	if (MS_PARA_SPE0 == curr->type)
		return (ms_exp_parameter_replace_spe0(curr, env, "WIP")); //
	else if (MS_PARA_NAME == curr->type)
		return (ms_exp_parameter_replace_name(curr, env, data));
	return (MS_SUCCESS);
}
