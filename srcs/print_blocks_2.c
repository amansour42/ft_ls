/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 09:58:47 by amansour          #+#    #+#             */
/*   Updated: 2018/04/03 09:59:22 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		type(struct stat buffer)
{
	char	t;

	t = '?';
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
	else if (S_ISREG(buffer.st_mode) == 1)
		t = '-';
	ft_printf("%c", t);
}

void		rights(struct stat sb)
{
	char	r[10];

	ft_strcpy(r, "---------");
	((sb.st_mode & S_IRUSR) == S_IRUSR) ? r[0] = 'r' : 0;
	((sb.st_mode & S_IWUSR) == S_IWUSR) ? r[1] = 'w' : 0;
	((sb.st_mode & S_IXUSR) == S_IXUSR) ? r[2] = 'x' : 0;
	((sb.st_mode & S_IRGRP) == S_IRGRP) ? r[3] = 'r' : 0;
	((sb.st_mode & S_IWGRP) == S_IWGRP) ? r[4] = 'w' : 0;
	((sb.st_mode & S_IXGRP) == S_IXGRP) ? r[5] = 'x' : 0;
	((sb.st_mode & S_IROTH) == S_IROTH) ? r[6] = 'r' : 0;
	((sb.st_mode & S_IWOTH) == S_IWOTH) ? r[7] = 'w' : 0;
	((sb.st_mode & S_IXOTH) == S_IXOTH) ? r[8] = 'x' : 0;
	if (sb.st_mode & S_ISUID)
		r[2] = (sb.st_mode & S_IXUSR) ? 's' : 'S';
	if (sb.st_mode & S_ISGID)
		r[5] = (sb.st_mode & S_IXGRP) ? 's' : 'l';
	if (sb.st_mode & S_ISVTX)
		r[8] = (sb.st_mode & S_IXOTH) ? 't' : 'T';
	ft_printf("%s ", r);
}

void		total(t_path *list)
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
