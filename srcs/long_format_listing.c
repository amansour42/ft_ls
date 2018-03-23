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

static int			length_nbr(long long nbr)
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

static int			big_nlink(t_path *list)
{
	struct stat	sb;
	t_path		*tmp;
	int			big;

	tmp = list;
	big = 0;
	while (tmp)
	{
		if (lstat(tmp->path, &sb) != -1)
			(sb.st_nlink > big) ? big = sb.st_nlink : 0;
		tmp = tmp->next;
	}
	return (length_nbr(big));
}

static long long	big_size(t_path *list)
{
	struct stat		sb;
	t_path			*tmp;
	t_device		device;
	int				big;

	tmp = list;
	big = 0;
	while (tmp)
	{
		if (lstat(tmp->path, &sb) != -1)
		{
			if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
			{
				(device.maj < major(sb.st_rdev)) ? device.maj = major(sb.st_rdev) : 0;
				(device.min < minor(sb.st_rdev)) ? device.maj = minor(sb.st_rdev) : 0;
				((device.maj + device.min + 2) > big) ? big = (device.maj + device.min + 2) : 0;
			}
			else
				(sb.st_size > big) ? big = sb.st_size : 0;
		}
		tmp = tmp->next;
	}
	return (length_nbr(big));
}

static void			special_print_2(long long nbr, int len)
{
	int i;

	i = len - length_nbr(nbr) + 1;
	while (i)
	{
		ft_printf(" ");
		--i;
	}
	ft_printf("%lld", nbr);
}

static void			special_print(struct stat info, int len)
{
	if (S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode))
	{	
		ft_printf("%ld, %ld ", major(info.st_rdev), minor(info.st_rdev));
		return ;
	}
	special_print_2(info.st_size, len);
}

void				print_with_blocks(t_path *list, char *str)
{
	struct stat	buffer;
	t_path		*tmp;
	int			nbr_nlink;
	int			nbr_size;

	tmp = list;
	nbr_nlink = big_nlink(list);
	nbr_size = big_size(list);
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
		special_print_2(buffer.st_nlink, nbr_nlink);
		(getpwuid(buffer.st_uid)) ? ft_printf(" %s", getpwuid(buffer.st_uid)->pw_name) : ft_printf(" %d", buffer.st_uid);
		(getgrgid(buffer.st_gid)) ? ft_printf(" %s ", getgrgid(buffer.st_gid)->gr_name) : ft_printf(" %d ", buffer.st_gid);
		special_print(buffer, nbr_size);
		ft_printf(" %.12s %s", (ctime(&buffer.st_mtime)) + 4,
				(tmp->path) + ft_strlen(str));
		(S_ISLNK(buffer.st_mode) == 1) ? print_link(tmp->path, buffer) :
		ft_printf("\n");
		tmp = tmp->next;
	}
}
