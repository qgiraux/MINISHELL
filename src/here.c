/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:02:15 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/25 14:07:17 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here.h"
#include "here_utils.h"
#include "fprintf.h"

static void	_warning(char *delimiter)
{
	t_csd		args;
	const char	*s[4] = {MS_E, MS_WHERE_MSG, delimiter, NULL};

	ms_fprintf_args(NULL, s, NULL, &args);
	ms_fprintf(STDERR_FILENO, MS_WHERE, &args);
}

static int	_unlink_entry(struct dirent *ent, const size_t len)
{
	char	*name;
	char	*cat;
	char	buff[100];
	size_t	len_cat;

	if (NULL == ent)
		return (MS_SUCCESS);
	name = ent->d_name;
	if (name == ft_strnstr(ent->d_name, MS_HERE_FILE, len + 1))
	{
		cat = buff;
		len_cat = strlen(MS_TMP_FOLDER);
		ft_memcpy(cat, MS_TMP_FOLDER, len_cat);
		ft_memcpy(cat + len_cat, "/", 1);
		cat += len_cat + 1;
		len_cat = strlen(name);
		ft_memcpy(cat, name, len_cat + 1);
		if (-1 == unlink(buff))
			return (ms_perror(MS_E), 1);
	}
	return (MS_SUCCESS);
}

/* ms_here_rm_tmp:
 * Removes tmp files in tmp folder
 */
int	ms_here_rm_tmp(void)
{
	struct dirent	*ent;
	DIR				*tmp;
	const size_t	len = ft_strlen(MS_HERE_FILE);

	tmp = opendir(MS_TMP_FOLDER);
	if (NULL == tmp || errno)
		return (ms_perror(MS_E), 1);
	ent = readdir(tmp);
	while (ent && 0 == errno)
	{
		if (_unlink_entry(ent, len))
			return (ms_e(__FILE__, __LINE__, 0), 1);
		if (0 == errno)
			ent = readdir(tmp);
	}
	if ((NULL == ent && errno))
		return (ms_perror(MS_E), 1);
	closedir(tmp);
	return (MS_SUCCESS);
}

/* ms_here:
 * here doc
 * writes in file descripter <fd_doc> EOF is <delimiter>
 * here doc read ends iff:
 * error OR a line has the exact value of <delimiter> OR ctrl+D on an empty line
 */
int	ms_here(int fd_doc, char *delimiter)
{
	t_dlist	*doc;
	int		errnum;
	char	*str;
	size_t	len;

	if (-1 == fd_doc || NULL == delimiter || '\0' == *delimiter)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	doc = NULL;
	errnum = ms_here_read(delimiter, &doc);
	if (MS_WEOF == errnum)
	{
		_warning(delimiter);
		len = 0;
	}
	else if (errnum)
		return (ms_e(__FILE__, __LINE__, 0), 1);
	else
		len = ft_strlen(delimiter);
	if (ms_here_tomstr(&str, len, doc))
		return (ms_e(__FILE__, __LINE__, 0), 1);
	ft_putstr_fd(str, fd_doc);
	return (free(str), MS_SUCCESS);
}

// // // // //

// int main(int ac, char **av)
// {
// 	int	fd = 1;

// 	if (2 != ac)
// 		return (1);
// 	printf("delimiter:%s\n", av[1]);
// 	ms_here(fd, av[1]);
// 	return (0);
// }
