/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:16:43 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/19 16:36:53 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

extern volatile sig_atomic_t	g_signum;

int		ms_sig_handle(void (*handler)(int), int restart);
int		ms_sig_int_act(void (*handler)(int), int restart);
int		ms_sig_quit_ignore(int restart);
int		ms_sig_ignore(int signum, int restart);

#endif