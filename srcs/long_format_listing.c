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

static t_device	init_device(void)
{
	t_device d;

	d.big = 0;
	d.maj = 0;
	d.min = 0;
	d.usr = 0;
	d.grp = 0;
	d.link = 0;
	return (d);
}

static void		usr_grp_max(struct stat sb, t_device *d)
{
	if (getpwuid(sb.st_uid))
		d->usr = MAX(d->usr, (int)ft_strlen(getpwuid(sb.st_uid)->pw_name));
	else
		d->usr = MAX(length_nbr(sb.st_uid), d->usr);
	if (getgrgid(sb.st_gid))
		d->grp = MAX((int)ft_strlen(getgrgid(sb.st_gid)->gr_name), d->grp);
	else
		d->grp = MAX(length_nbr(sb.st_gid), d->grp);
}

static t_device	big_size(t_path *list)
{
	struct stat		sb;
	t_path			*tmp;
	t_device		d;

	tmp = list;
	d = init_device();
	while (tmp)
	{
		if (lstat(tmp->path, &sb) != -1)
		{
			if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
			{
				d.maj = MAX(d.maj, length_nbr(major(sb.st_rdev)));
				d.min = MAX(d.min, length_nbr(minor(sb.st_rdev)));
				if ((d.maj + d.min + 3) > d.big)
					d.big = d.maj + d.min + 3;
			}
			else
				d.big = MAX(length_nbr(sb.st_size), d.big);
			d.link = MAX(length_nbr(sb.st_nlink), d.link);
			usr_grp_max(sb, &d);
		}
		tmp = tmp->next;
	}
	return (d);
}

void			print_with_blocks(t_path *list, char *str)
{
	struct stat	buffer;
	t_path		*tmp;
	t_device	d;

	tmp = list;
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
		(S_ISLNK(buffer.st_mode) == 1) ? llink(tmp->path) : ft_printf("\n");
		tmp = tmp->next;
	}
}
