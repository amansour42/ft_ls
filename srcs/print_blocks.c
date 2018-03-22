/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:32:13 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:48:04 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	type(struct stat buffer)
{
	char	t;

	t = '-';
	if (S_ISLNK(buffer.st_mode) == 1)
		t = 'l';
	else if (S_ISDIR(buffer.st_mode) == 1)
		t = 'd';
	else if (S_ISBLK(buffer.st_mode) == 1)
		t = 'b';
	else if (S_ISCHR(buffer.st_mode) == 1)
		t = 'c';
	else if (S_ISFIFO(buffer.st_mode) == 1)
		t = 'p';
	else if (S_ISSOCK(buffer.st_mode) == 1)
		t = 's';
	ft_printf("%c", t);
}

void	rights(struct stat buffer)
{
	char	r[10];

	ft_strcpy(r, "---------");
	((buffer.st_mode & S_IRUSR) == S_IRUSR) ? r[0] = 'r' : 0;
	((buffer.st_mode & S_IWUSR) == S_IWUSR) ? r[1] = 'w' : 0;
	((buffer.st_mode & S_IXUSR) == S_IXUSR) ? r[2] = 'x' : 0;
	((buffer.st_mode & S_IRGRP) == S_IRGRP) ? r[3] = 'r' : 0;
	((buffer.st_mode & S_IWGRP) == S_IWGRP) ? r[4] = 'w' : 0;
	((buffer.st_mode & S_IXGRP) == S_IXGRP) ? r[5] = 'x' : 0;
	((buffer.st_mode & S_IROTH) == S_IROTH) ? r[6] = 'r' : 0;
	((buffer.st_mode & S_IWOTH) == S_IWOTH) ? r[7] = 'w' : 0;
	((buffer.st_mode & S_IXOTH) == S_IXOTH) ? r[8] = 'x' : 0;
	ft_printf("%s ", r);
}

void	total(t_path *list)
{
	struct stat		sb;
	t_path			*tmp;
	long long		total;

	tmp = list;
	total = 0;
	while (tmp)
	{
		lstat(tmp->path, &sb);
		total += sb.st_blocks;
		tmp = tmp->next;
	}
	ft_printf("total %lld\n", total);
}

void	print_link(char *s2, struct stat buffer)
{
	char *buf;

	if (!(buf = malloc(buffer.st_size)))
		error("malloc");
	if ((readlink(s2, buf, buffer.st_size)) == -1)
		error("readlink");
	buf[buffer.st_size] = '\0';
	ft_printf(" -> %s\n", buf);
	free(buf);
}
