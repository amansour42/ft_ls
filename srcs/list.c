/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:46:10 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:33:09 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_list(t_path **path, char *str)
{
	t_path *tmp;
	t_path *list;

	tmp = NULL;
	if ((tmp = (t_path*)malloc(sizeof(t_path))))
	{
		tmp->path = ft_strdup(str);
		tmp->next = NULL;
		if (!*path)
			*path = tmp;
		else
		{
			list = *path;
			while (list->next)
				list = list->next;
			list->next = tmp;
		}
	}
	else
		error("malloc", path);
}

int			length_list(t_path *path)
{
	t_path	*tmp;
	int		len;

	len = 0;
	tmp = path;
	while (tmp)
	{
		tmp = tmp->next;
		++len;
	}
	return (len);
}

void		delete_list(t_path **path)
{
	t_path *p;

	while (*path)
	{
		p = *path;
		*path = (*path)->next;
		free(p->path);
		free(p);
	}
}

void		delete_link(t_path **path, t_path *d)
{
	t_path *p;
	t_path *tmp;

	tmp = NULL;
	p = *path;
	while (p && p->path != d->path)
	{
		tmp = p;
		p = p->next;
	}
	if (!tmp)
	{
		*path = (*path)->next;
		free(p->path);
		free(p);
		return ;
	}
	tmp->next = p->next;
	free(p->path);
	free(p);
}

void		list_to_path(t_path **list, char *str)
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
