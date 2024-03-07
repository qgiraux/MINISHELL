/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parameter_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/07 16:23:48 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_utils.h"
#include "env.h"

static char	*ms_data_get_pipeline_exit(void *data)
{
	return ((char *)data); //
}

static int	ms_exp_parameter_replace_name(t_dlist *curr, char **env, void *data)
{
	char	*str;
	char	*escpd_content;

	(void)data;
	(void)env;
	if (NULL == curr->content)
		return (1); //
	if (ms_env_get_str((const char **)env, (char *)(curr->content) + 1, &str))
		return (1);
	if (NULL == str)
		escpd_content = ft_strdup(""); //
	else
		escpd_content = ms_exp_escape(str, EXP_ESC_LIST); //
	if (NULL == escpd_content)
		return (1); //
	free(curr->content);
	curr->content = escpd_content;
	curr->type = MS_PARA_STR;
	return (0);
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
	int	err;

	err = 0;
	if (MS_PARA_SPE0 == curr->type)
		err = ms_exp_parameter_replace_spe0(curr, env, "WIP"); //
	else if (MS_PARA_NAME == curr->type)
		err = ms_exp_parameter_replace_name(curr, env, data);
	if (!err)
	{
		; //
	}
	return (err);
}
