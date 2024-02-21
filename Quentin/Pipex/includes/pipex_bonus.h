/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:08:17 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/19 10:55:53 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_fct
{
	char	***function;
	char	**fct;
	int		*pid;
	char	**argv;	
	int		**pipefd;
	int		*status;
	int		argc;
	char	**env;
	int		tmp;
	int		cat;
}			t_fct;

typedef struct s_mainvar
{
	char	**argv;
	int		argc;
	char	**env;
	int		cat;
}			t_mainvar;

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
void		free_all(t_fct f);
void		free_split(char **str);
t_fct		init_bonus(char **argv, int argc, char **env);
int			pipe_loop_bonus(t_fct f, int argc, char **argv);
char		*ft_strdup(const char *str);
char		*check_paths(char *str, char **env, int i);
int			ft_strncmp(const char *s1, const char *s2, size_t len);
int			for_child(t_fct f, int i, int in);
int			did_child_work(t_fct f, int i, int in);
t_mainvar	is_it_here(t_mainvar m);
t_mainvar	init_mainvar(int argc, char **argv, char **env);
char		*get_next_line(int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *str, int c);

#endif
