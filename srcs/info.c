/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 10:31:51 by amansour          #+#    #+#             */
/*   Updated: 2017/12/07 11:16:48 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	type(struct stat sb, char **str)
{
	if (sb.st_mode == S_IFBLK)
		*str = ft_strdup("BLOC");
	else if (sb.st_mode == S_IFCHR)
		*str = ft_strdup("CHARACTER");
	else if (sb.st_mode == S_IFDIR)
		*str = ft_strdup("DIRECTORY");
	else if (sb.st_mode == S_IFIFO)
		*str = ft_strdup("FIFO");
	else if (sb.st_mode == S_IFLNK)
		*str = ft_strdup("LINK");
	else if (sb.st_mode == S_IFREG)
		*str = ft_strdup("REGULAR");
	else if (sb.st_mode == S_IFSOCK)
		*str = ft_strdup("SOKET");
	else
		*str = ft_strdup("UNKNOWN");
}
