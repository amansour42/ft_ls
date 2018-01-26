/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:46:10 by amansour          #+#    #+#             */
/*   Updated: 2018/01/26 16:22:13 by amansour         ###   ########.fr       */
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
	return ;
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

void		copy_data(t_path **path, t_path *to_copy)
{
	t_path *tmp;
	t_path *list;

	tmp = NULL;
	if ((tmp = (t_path*)malloc(sizeof(t_path))))
	{
		tmp->path = ft_strdup(to_copy->path);
		tmp->time = to_copy->time;
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
}

void		delete_link(t_path **path, t_path *d)
{
	t_path *p;
	t_path *tmp;

	tmp = NULL;
	p = *path;
	while (p && p->path != d->path && p->time != d->time)
  {
    tmp = p;
    p = p->next;
  }
  if (!tmp)
  {
    *path = (*path)->next;
    free(p->path);
    free(p->type);
    free(p);
    return ;
  }
  tmp->next = p->next;
  free(p->path);
  free(p->type);
  free(p);
}
