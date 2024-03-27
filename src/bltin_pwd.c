/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:36:21 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 15:17:58 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "bltin_utils.h"
#include "data.h"

static char	*_mget_cwd(size_t buff_len)
{
	const size_t	growth = BLTIN_BUFF_GROW;
	size_t			next_buff_len;
	char			*cwd;
	char			*buff;

	if (1 > buff_len)
		return (NULL);
	cwd = NULL;
	while (NULL == cwd)
	{
		buff = (char *)malloc(sizeof(char) * buff_len);
		if (NULL == buff)
			return (ms_perror(MS_E), NULL);
		cwd = getcwd(buff, buff_len);
		if (NULL == cwd)
		{
			free(buff);
			next_buff_len = growth * buff_len;
			if (next_buff_len < buff_len)
				return (NULL);
			buff_len = next_buff_len;
		}
	}
	return (cwd);
}

int	ms_bltin_pwd(char **av, void *data)
{
	char		*cwd;
	int			f_out;

	(void)av;
	cwd = _mget_cwd(BLTIN_BUFF_LEN);
	if (NULL == cwd)
		return (ms_e(__FILE__, __LINE__, 0), 1);
	ms_data_redir_get(NULL, &f_out, data);
	ft_putstr_fd(cwd, f_out);
	free(cwd);
	write(f_out, BLTIN_NEWLINE, 1);
	return (MS_SUCCESS);
}

//Malloc proofread