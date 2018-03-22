/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:25:00 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 08:25:03 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_path		*files(char *str)
{
	DIR				*dir;
	struct dirent	*flow;
	t_path			*files;

	files = NULL;
	if ((dir = opendir(str)))
	{
		while ((flow = readdir(dir)))
			add_list(&files, flow->d_name);
	}
	else
		error("ERROR");
	closedir(dir);
	sort(&files);
	return (files);
}

static void			list_to_print(t_path **l)
{
	t_path *tmp;
	t_path *new;

	tmp = *l;
	new = NULL;
	while (tmp)
	{
		if (tmp->path[0] != '.')
			add_list(&new, tmp->path);
		tmp = tmp->next;
	}
	delete_list(l);
	*l = new;
}

static void			list_to_path(t_path **list, char *str)
{
	t_path	*tmp;
	t_path	*new;
	char	*s;

	tmp = *list;
	new = NULL;
	while (tmp)
	{
		s = ft_strjoin(str, tmp->path);
		add_list(&new, s);
		tmp = tmp->next;
		free(s);
	}
	delete_list(list);
	*list = new;
}

static void			print_minus_one(t_path *list, char *s)
{
	t_path *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		ft_printf("%s\n", tmp->path + ft_strlen(s));
		tmp = tmp->next;
	}
	if (tmp)
		ft_printf("%s\n", tmp->path + ft_strlen(s));
}

void				print_list(int flag, char *str)
{
	t_path			*path;
	struct winsize	w;
	char			*s;

	path = files(str);
	((flag & A) == 0) ? list_to_print(&path) : 0;
	if (path == NULL)
		return ;
	s = ft_strjoin(str, "/");
	list_to_path(&path, s);
	if (flag & R)
		reverse_list(&path);
	else if (flag & T)
		time_listing(&path);
	if (flag & L)
		print_with_blocks(path, s);
	else if ((flag & MINUS) == 0 && isatty(STDOUT_FILENO))
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		column_display(&path, w, length_list(path), ft_strlen(s));
	}
	else
		print_minus_one(path, s);
	free(s);
	delete_list(&path);
}
