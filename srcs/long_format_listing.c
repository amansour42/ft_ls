/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_listing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:33:43 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 09:02:51 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				length_nbr(long long nbr)
{
	int nb;

	nb = 1;
	while (nbr / 10)
	{
		++nb;
		nbr /= 10;
	}
	return (nb);
}

static t_device	big_size(t_path *list)
{
	struct stat		sb;
	t_path			*tmp;
	t_device		d;

	tmp = list;
	d.big = 0;
	d.maj = 0;
	d.min = 0;
	d.usr = 0;
	d.grp = 0;
	d.link = 0;
	while (tmp)
	{
		if (lstat(tmp->path, &sb) != -1)
		{
			if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
			{
				(d.maj < length_nbr(major(sb.st_rdev))) ? d.maj = length_nbr(major(sb.st_rdev)) : 0;
				(d.min < length_nbr(minor(sb.st_rdev))) ? d.min = length_nbr(minor(sb.st_rdev)) : 0;
				((d.maj + d.min + 3) > d.big) ? d.big = (d.maj + d.min + 3) : 0;
			}
			else 
				(length_nbr(sb.st_size > d.big)) ? d.big = length_nbr(sb.st_size) : 0;
			(length_nbr(sb.st_nlink) > d.link) ? d.link = length_nbr(sb.st_nlink) : 0;
			if (getpwuid(sb.st_uid))
				(ft_strlen(getpwuid(sb.st_uid)->pw_name) > (size_t)d.usr) ? d.usr = ft_strlen(getpwuid(sb.st_uid)->pw_name): 0;
			else
				(length_nbr(sb.st_uid) > d.usr) ? d.usr = length_nbr(sb.st_uid) : 0;
			if (getgrgid(sb.st_gid))
				(ft_strlen(getgrgid(sb.st_gid)->gr_name) > (size_t)d.grp) ? d.grp = ft_strlen(getgrgid(sb.st_gid)->gr_name): 0;
			else
				(length_nbr(sb.st_gid) > d.usr) ? d.usr = length_nbr(sb.st_gid) : 0;
		}
		tmp = tmp->next;
	}
	return (d);
}

static void			special_print(struct stat info, t_device d)
{
	if (S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode))
	{
		special_print_2(major(info.st_rdev), d.maj);
		ft_printf(", ");
		special_print_2(minor(info.st_rdev), d.min);
		return ;
	}
	special_print_2(info.st_size, d.big);
}

void				print_with_blocks(t_path *list, char *str)
{
	struct stat	buffer;
	t_path		*tmp;
	//int			nbr_nlink;
	t_device	d;

	tmp = list;
	//nbr_nlink = big_nlink(list);
	d = big_size(list);
	(str) ? total(list) : 0;
	while (tmp)
	{
		if (lstat(tmp->path, &buffer) == -1)
		{
			printf("ERROR: Permission denied\n");
			tmp = tmp->next;
			continue;
		}
		type(buffer);
		rights(buffer);
		special_print_2(buffer.st_nlink, d.link);
		print_usr_grp(buffer, d);
		special_print(buffer, d);
		ft_printf(" %.12s %s", (ctime(&buffer.st_mtime)) + 4,
				(tmp->path) + ft_strlen(str));
		(S_ISLNK(buffer.st_mode) == 1) ? print_link(tmp->path, buffer) :
		ft_printf("\n");
		tmp = tmp->next;
	}
}
