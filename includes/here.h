/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 13:05:19 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_H
# define HERE_H

# define MS_HERE_PATH "/tmp/minishell-heredoc-"

int		ms_here(int fd_doc, char *delimiter);
int		ms_here_rm_tmp(void);

#endif