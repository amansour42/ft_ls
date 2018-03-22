/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:20:01 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:22:43 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ptr_del(t_path **p)
{
	free(*p);
	*p = NULL;
}

void		reverse_list(t_path **list)
{
	t_path *res;
	t_path *ptmp;
	t_path *tmp;

	res = NULL;
	while (*list)
	{
		tmp = *list;
		ptmp = (*list)->next;
		while (ptmp && ptmp->next)
		{
			tmp = ptmp;
			ptmp = ptmp->next;
		}
		(ptmp) ? add_list(&res, ptmp->path) : add_list(&res, (*list)->path);
		(ptmp) ? free(ptmp->path) : free((*list)->path);
		if (ptmp)
			ptr_del(&ptmp);
		else
			ptr_del(list);
	}
	*list = res;
}
