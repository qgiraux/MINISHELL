/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgiraux <qgiraux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:16 by qgiraux           #+#    #+#             */
/*   Updated: 2024/01/22 14:26:01 by qgiraux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	end(char *input, int tmp)
{
	free (input);
	close(tmp);
	unlink("here_doc");
	write(1, "invalid entry, it should end with the limiter\n", 46);
	return ;
}

static t_mainvar	found_here(t_mainvar m, char *input, int tmp)
{
	int	i;

	m.argv[1] = "here_doc";
	i = 1;
	while (++i < m.argc - 1)
		m.argv[i] = m.argv[i + 1];
	m.argc--;
	close(tmp);
	free (input);
	return (m);
}

t_mainvar	is_it_here(t_mainvar m)
{
	char	*input;
	int		tmp;

	if (ft_strncmp(m.argv[1], "here_doc", 8) != 0)
		return (m.cat = 0, m);
	m.cat = 1;
	tmp = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	input = get_next_line(0);
	while (input != NULL)
	{
		if (input == 0)
			break ;
		if (ft_strncmp(input, m.argv[2], ft_strlen(m.argv[2])) == 0
			&& (ft_strlen(input) == ft_strlen(m.argv[2]) + 1))
			return (found_here(m, input, tmp));
		write(tmp, input, ft_strlen(input));
		free (input);
		input = get_next_line(0);
	}
	return (end (input, tmp), m);
}
