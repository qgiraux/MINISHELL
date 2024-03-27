/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerperez <jerperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:04 by qgiraux           #+#    #+#             */
/*   Updated: 2024/03/25 14:29:32 by jerperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fprintf.h"
#include "fprintf_utils.h"

static void	_c(char **format, size_t *i, char *buff, t_csd *args)
{
	*format += 2;
	if (NULL == args->c)
		return ;
	if (*(args->c) && *i < MS_BUFF_LEN)
		buff[(*i)++] = *(args->c);
	if ('\0' != *(args->c))
		args->c += 1;
}

static void	_s(char **format, size_t *i, char *buff, t_csd *args)
{
	char	*s;

	*format += 2;
	if (NULL == args->s)
		return ;
	s = *(args->s);
	if (NULL == s)
		return ;
	while (*s && *i < MS_BUFF_LEN)
		buff[(*i)++] = *s++;
	args->s += 1;
}

static void	ms_fprintf_var(char **format, size_t *i, char *buff, t_csd *args)
{
	while ('%' == **format && *i < MS_BUFF_LEN)
	{
		if ('c' == *(*format + 1))
			_c(format, i, buff, args);
		else if ('s' == *(*format + 1))
			_s(format, i, buff, args);
		else if ('d' == *(*format + 1))
			ms_fprintf_d(format, i, buff, args);
		else
			buff[(*i)++] = *((*format)++);
	}
}

/* ms_fprintf_args:
 * puts c, s, d into <args>
 * c/s/d are const or NULL
 * c/s/d should be terminated when possible
 * ----------------------------------
 * Example: (prints 'TEST: THIS IS 0k')
 * ----------------------------------
 * t_csd		args;
 * const char	*c = "k";
 * const char	*s[3] = {"THIS IS", "NOT READ", NULL};
 * const int	d[2] = {0, 0};
 * 
 * ms_fprintf_args(c, s, d, &args);
 * ms_fprintf(1, "TEST: %s %d%c\n", &args);
 * -----------------------------------
 */
void	ms_fprintf_args(\
	const char *c, const char **s, const int *d, t_csd *args)
{
	args->c = (char *)c;
	args->s = (char **)s;
	args->d = (int *)d;
}

/* ms_fprintf:
 * Writes formated string on file
 * Write accurately up to MS_BUFF_LEN chars until args might be cropped
 * Can be used with <ms_fprintf_args> to help fill <args> with c s d
 * (c) and (s) can be protected against buffer overflow with '\0' and NULL
 * Decimals (d) are not protected
 * Buffer overflow will result in ramdom memory read
 */
int	ms_fprintf(int fd, char *format, t_csd *args)
{
	char	buff[MS_BUFF_LEN];
	size_t	i;
	size_t	len;
	int		len_fprintf;

	len_fprintf = 0;
	while (NULL != format && NULL != args && *format)
	{
		i = 0;
		while (*format && i < MS_BUFF_LEN)
		{
			ms_fprintf_var(&format, &i, buff, args);
			while ('\0' != *format && '%' != *format && i < MS_BUFF_LEN)
				buff[i++] = *format++;
		}
		if (i > MS_BUFF_LEN)
			buff[MS_BUFF_LEN - 1] = '\0';
		else
			buff[i] = '\0';
		len = 0;
		while (buff[len])
			len++;
		len_fprintf += write(fd, buff, len);
	}
	return (len_fprintf);
}

// int main(int ac, char **av)
// {
// 	t_csd		args;
// 	const char	*c = "LOL";
// 	//const char	*s[2] = {"THIS", NULL};
// 	const int	d[4] = {1325435, 2147483647, -2147483648, 0};

// 	(void)ac;
// 	(void)av;
// 	ms_fprintf_args(c, NULL, d, &args);
// 	ms_fprintf(1, "ms: %s is an erro at %ds\n", &args);
// }
