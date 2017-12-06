/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:21:19 by amansour          #+#    #+#             */
/*   Updated: 2017/12/06 16:56:33 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				empty_list(t_path *l)
{
	t_path	*p;

	p = l;
	while (p)
	{
		if (ft_strcmp(p->path, ""))
			return (0);
		p = p->next;
	}
	return (1);
}

void			put_null(t_path **l, char *str)
{
	t_path *list;

	list = *l;
	while (list && ft_strcmp(str, list->path))
		list = list->next;
	free(list->path);
	list->path = ft_strdup("");
}

void			sort(t_path **list)
{
	t_path	*l;
	char	*str;
	t_path	*res;
	t_path	*tmp;

	l = *list;
	res = NULL;
	while (!empty_list(l))
	{
		tmp = l;
		while (tmp && !ft_strcmp(tmp->path, ""))
			tmp = tmp->next;
		str = tmp->path;
		tmp = tmp->next;
		while (tmp)
		{
			if (ft_strcmp(tmp->path, str) < 0)
				str = tmp->path;
			tmp = tmp->next;
		}
		add_list(&res, str);
		put_null(&l, str);
	}
	delete_list(list);
	*list = res;
}
