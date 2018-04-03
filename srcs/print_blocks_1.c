/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 09:56:20 by amansour          #+#    #+#             */
/*   Updated: 2018/04/03 09:56:52 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		llink(char *s2)
{
	char	buf[NAME_MAX + 1];

	readlink(s2, buf, NAME_MAX);
	ft_printf(" -> %s\n", buf);
}

void		special_print(struct stat info, t_device d)
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

void		print_usr_grp(struct stat buffer, t_device d)
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
