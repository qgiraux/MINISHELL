/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_filename_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:55:30 by jerperez          #+#    #+#             */
/*   Updated: 2024/03/09 14:38:42 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "exp_utils.h"
#include "error.h"

static int	ms_exp_filename_list_sort(t_dlist *prev, t_dlist *next)
{
	char	*str1;
	char	*str2;
	size_t	i;
	int		case_diff;

	str1 = (char *)(prev->content);
	str2 = (char *)(next->content);
	i = 0;
	case_diff = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			if (ft_tolower(str1[i]) == ft_tolower(str2[i]))
			{
				if (0 == case_diff)
					case_diff = str1[i] < str2[i];
			}
			else
				return (ft_tolower(str1[i]) < ft_tolower(str2[i]));
		}
		i++;
	}
	return ((ft_tolower(str1[i]) < ft_tolower(str2[i])) || case_diff);
}

static void	ms_dlstadd_sort(\
	t_dlist **lst, t_dlist *new, int (*comp)(t_dlist *, t_dlist*))
{
	t_dlist	*curr;
	t_dlist	*prev;

	if (NULL == lst)
		return ;
	if (!*lst)
		return ((void)ms_dlstadd_back(lst, new));
	new->next = NULL;
	prev = NULL;
	curr = *lst;
	while (curr && comp(curr, new))
	{
		prev = curr;
		curr = curr->next;
	}
	new->prev = prev;
	new->next = curr;
	if (curr)
		curr->prev = new;
	if (prev)
		prev->next = new;
	else
		*lst = new;
}

static int	ms_exp_filename_list_madd(t_dlist **files, char *name, int type)
{
	t_dlist			*new;
	char			*str;

	if (NULL == name || NULL == files)
		return (ms_e(__FILE__, __LINE__, 1), 1);
	str = ft_strdup(name);
	if (NULL == str)
		return (ms_perror(MS_E), 1);
	new = ms_dlstnew(str, type);
	if (NULL == new)
		return (free(str), ms_perror(MS_E), 1);
	ms_dlstadd_sort(files, new, &ms_exp_filename_list_sort);
	return (MS_SUCCESS);
}

static int	ms_exp_filename_list_mall(DIR *d, t_dlist **files)
{
	struct dirent	*dir;

	errno = 0;
	dir = readdir(d);
	while (dir && 0 == errno)
	{
		if (0 == errno)
			dir = readdir(d);
		if (NULL != dir)
			if (ms_exp_filename_list_madd(files, dir->d_name, MS_PARA_STR))
				return (ms_e(__FILE__, __LINE__, 0), 1);
	}
	if ((NULL == dir && errno))
		return (perror(MS_E), ms_dlstclear(files), 1);
	return (MS_SUCCESS);
}

int	ms_exp_filename_list_cwd(t_dlist **files, void *data)
{
	DIR		*cwd;

	*files = ms_data_cwd_list_get(data);
	if (NULL != *files)
		return (MS_SUCCESS);
	*files = NULL;
	cwd = opendir(EXP_CWD);
	if (NULL == cwd)
		return (1);
	if (ms_exp_filename_list_mall(cwd, files))
		return (ms_e(__FILE__, __LINE__, 0), \
			ms_dlstclear(files), closedir(cwd), 1);
	closedir(cwd);
	if (NULL != *files)
	{
		if (ms_exp_filename_list_madd(files, EXP_CWD, MS_PARA_STR))
			return (ms_e(__FILE__, __LINE__, 0), \
				ms_dlstclear(files), 1);
	}
	ms_data_cwd_list_set(files, &data); //WIP
	return (MS_SUCCESS);
}

// int main(int ac, char **av)
// {
// 	t_dlist	*files;
// 	void	*data;

// 	data = NULL;
// 	ms_exp_filename_list_cwd(&files, data);
// 	while (files)
// 	{
// 		printf("%s\n", (char *)(files->content));
// 		files = files->next;
// 	}
// 	return (0);
// }
