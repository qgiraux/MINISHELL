/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/02/29 14:09:02 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_utils.h"

// void	debug_data_read(void *data)
// {
// 	char	buff[100];
// 	t_redir	*data_redir;
// 	int		f1;
// 	int		f2;

// 	data_redir = (t_redir *)data;
// 	ms_redir_data_get(&f1, &f2, data_redir);
// 	printf("f1 %d f2 %d\n", f1, f2);
// 	if (f1 > 2)
// 		printf("in:%d\n", read(f1, buff, 100));
// 	if (f2 > 2)
// 		printf("out:%d\n", read(4, buff, 100));
// }

void	ms_redir_data_set(int fid_in, int fid_out, void *data)
{
	t_redir	*data_redir;

	data_redir = (t_redir *)data;
	if (-1 < fid_in)
		data_redir->fid_in = fid_in;
	if (-1 < fid_out)
		data_redir->fid_out = fid_out;
}

void	ms_redir_data_get(int *fid_in, int *fid_out, void *data)
{
	t_redir	*data_redir;

	data_redir = (t_redir *)data;
	if (fid_in)
		*fid_in = data_redir->fid_in;
	if (fid_out)
		*fid_out = data_redir->fid_out;
}

void	ms_redir_data_ini(void **data)
{
	t_redir	*data_redir;

	data_redir = malloc(sizeof(t_redir));
	data_redir->fid_in = STDIN_FILENO;
	data_redir->fid_out = STDOUT_FILENO;
	*data = data_redir;
}

void	ms_redir_data_destroy(void **data)
{
	t_redir	*data_redir;

	data_redir = (t_redir *)(*data);
	ms_redir_file_close_all(data_redir);
	free(data_redir);
	*data = NULL;
}
