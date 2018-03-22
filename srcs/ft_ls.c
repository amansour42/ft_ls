/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:53:36 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:46:58 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_path	*files(char *str)
{
	DIR				*dir;
	struct dirent	*flow;
	t_path			*files;
	char			*s[2];

	files = NULL;
	s[0] = ft_strjoin(str, "/");
	if ((dir = opendir(str)))
		while ((flow = readdir(dir)))
		{
			if (ft_strcmp(flow->d_name, ".") && ft_strcmp(flow->d_name, ".."))
			{
				s[1] = ft_strjoin(s[0], flow->d_name);
				add_list(&files, s[1]);
				free(s[1]);
			}
			else
				add_list(&files, flow->d_name);
		}
	(dir) ? closedir(dir) : error("ERROR");
	sort(&files);
	free(s[0]);
	return (files);
}

static int		is_dir(char *str)
{
	struct stat sb;

	if (lstat(str, &sb) == -1)
		error("lstat");
	return ((S_ISDIR(sb.st_mode) == 1) ? 1 : 0);
}

void			ft_ls(int flag, char *str)
{
	t_path	*path;
	t_path	*tmp;

	print_list(flag, str);
	if ((flag & BIGR) == 0)
		return ;
	path = files(str);
	tmp = path;
	while (tmp)
	{
		while (tmp && (!is_dir(tmp->path) || !ft_strcmp(tmp->path, "..")
				|| !ft_strcmp(tmp->path, ".")))
			tmp = tmp->next;
		if (tmp)
		{
			ft_printf("\n%s:\n", tmp->path);
			ft_ls(flag, tmp->path);
			tmp = tmp->next;
		}
	}
	delete_list(&path);
}
