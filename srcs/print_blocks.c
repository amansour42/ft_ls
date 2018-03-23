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

void		print_link(char *s2, struct stat buffer)
{
	char	*buf;
	int		r;

	if (!(buf = malloc(buffer.st_size + 1)))
		error("malloc");
	if ((r = (readlink(s2, buf, buffer.st_size + 1))) == -1)
		error("readlink");
	if (r > buffer.st_size)
	{
        ft_printf("la taille du lien symbolique a augmente entre lstat() et readlink()\n");
        return ;
    }
	buf[r] = '\0';
	ft_printf(" -> %s\n", buf);
	free(buf);
}

void		special_print_2(long long nbr, int len)
{
	int i;

	i = len - length_nbr(nbr) + 1;
	while (i > 0)
	{
		ft_printf(" ");
		--i;
	}
	ft_printf("%lld", nbr);
}

static void	special_print_3(char *str, int len)
{
	int i;

	i = len - ft_strlen(str) + 1;
	ft_printf(" %s", str);
	while (i > 0)
	{
		ft_printf(" ");
		--i;
	}
}

void	print_usr_grp(struct stat buffer, t_device d)
{
	if (getpwuid(buffer.st_uid))
		special_print_3(getpwuid(buffer.st_uid)->pw_name, d.usr);
	else
		special_print_2(buffer.st_uid, d.usr);
	if (getgrgid(buffer.st_gid))
		special_print_3(getgrgid(buffer.st_gid)->gr_name, d.grp);
	else
		special_print_2(buffer.st_gid, d.grp);
}