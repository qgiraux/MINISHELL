/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:09:43 by qgiraux           #+#    #+#             */
/*   Updated: 2024/02/23 11:20:47 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../includes/minishell.h"


SHELL EXPANSIONS
REDIRECTIONS
EXECUTE COMMAND
GET EXIT STATUS

int	ms_executeur(t_dlist *command_head)
{
	int	status;

	status = ms_is_it_here(command_head);
	if (status == 0)
		status = ms_expand(command_head);
	if (status == 0)
		status = ms_redirect(command_head);
	if (status == 0)
		status = ms_execute(command_head);
	return (status);
}

int	ms_is_it_here(t_dlist *command_head)
{
	t_dlist	*cmd;
	int		status;

	cmd = command_head;
	
	while (cmd)
	{
		if (cmd->type == MS_TOKEN_HERE_DOC)
			status = ms_make_here_doc(cmd);
		if (status != 0)
			return (status);
		cmd = cmd->next;
	}
	return (status);
}

int	ms_expand(t_dlist *command_head)
{
	t_dlist	*cmd;
	int		status;

	cmd = command_head;
	
	while (cmd)
	{
		if (cmd->type == MS_TOKEN_EXPAND)
			status = ms_replace_variable(cmd);
		if (status != 0)
			return (status);
		cmd = cmd->next;
	}
	return (status);
}

int	ms_redirect(t_dlist *command_head)
{
	t_dlist	*cmd;
	int		status;

	cmd = command_head;
	
	while (cmd)
	{
		if (cmd->type == MS_TOKEN_INTPUT)
			status = ms_change_input(cmd);
		else if (cmd->type == MS_TOKEN_OUTPUT)
			status = ms_change_output(cmd);
		else if (cmd->type == MS_TOKEN_APPEND)
			status = ms_change_output_append(cmd);
		else if (status != 0)
			return (status);
		else
			cmd = cmd->next;
	}
	return (status);
}

int	ms_execute(t_dlist *command_head)
{
	t_dlist	*cmd;
	int		status;

	cmd = command_head;	
}*/