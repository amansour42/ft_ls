/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 10:31:51 by amansour          #+#    #+#             */
/*   Updated: 2018/01/29 10:41:08 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	type(struct stat sb, char **str)
{
	if (sb.st_mode == S_IFBLK)
		*str = "BLOC";
	else if (sb.st_mode == S_IFCHR)
		*str = "CHARACTER";
	else if (sb.st_mode == S_IFDIR)
		*str = "DIRECTORY";
	else if (sb.st_mode == S_IFIFO)
		*str = "FIFO";
	else if (sb.st_mode == S_IFLNK)
		*str = "LINK";
	else if (sb.st_mode == S_IFREG)
		*str = "REGULAR";
	else if (sb.st_mode == S_IFSOCK)
		*str = "SOKET";
	else
		*str = "UNKNOWN";
}
