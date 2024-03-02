/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:55:18 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/15 15:14:09 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_LEN 100
# define ENV_HOME "HOME"

void	ft_error(char *bin, int errnum, int fd_error);
char	*ft_getenv(const char *name);
size_t	ft_strlen(char *str);
void	ft_bin_exit_status(int status);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strncat(char *dest, char *src, size_t n);
void	ft_memset(void *s, int c, size_t n);

#endif