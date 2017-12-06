/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:31:48 by amansour          #+#    #+#             */
/*   Updated: 2017/12/06 17:08:21 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path		*files(char *str)
{
	DIR				*dir;
	struct dirent	*flow;
	t_path			*files;

	files = NULL;
	if ((dir = opendir(str)))
		while ((flow = readdir(dir)))
			add_list(&files, flow->d_name);
	else
	{
		perror("ERROR");
		return (NULL);
	}
	sort(&files);
	return (files);
}

int		size(t_path *l)
{
	int		i;
	int		j;
	t_path	*tmp;

	tmp = l->next;
	i = ft_strlen(l->path);
	while(tmp)
	{
		j = ft_strlen(tmp->path);
		tmp = tmp->next;
		if (j > i)
			i = j;
	}
	return (j);
}

void		print_without_blocs(int flag, char *str)
{
	t_path	*path;
	int		length;
	t_path	*l;
	int		i;

	if (!(path = files(str)))
		return ;
	if (flag & R)
		reverse_list(&path);
	else if (flag & T)
		time_listing(&path);
	length = size(path);
	l = path;
	while (l && l->next)
	{
		if (l->path[0] == '.')
		{
			l = l->next;
			continue ;
		}
		ft_printf("%s ", l->path);
		i = ft_strlen(l->path) - 1;
		while (++i < length)
			ft_printf(" ");
		l = l->next;
	}
	(l->path[0] != '.') ? ft_printf("%s\n", l->path) : ft_printf("\n");
	delete_list(&path);
}
