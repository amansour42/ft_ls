/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:26:50 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:31:00 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_size(t_path *l, int n)
{
	int			i;
	int			j;
	t_path		*tmp;

	tmp = l;
	i = ft_strlen(l->path);
	while (tmp)
	{
		j = ft_strlen(tmp->path);
		tmp = tmp->next;
		if (j > i)
			i = j;
	}
	return (i - n);
}

static void		display_string(char *str, int max_size, int n)
{
	int h;

	ft_printf("%s", str + n);
	h = ft_strlen(str) - n;
	while (h <= max_size)
	{
		ft_printf(" ");
		h++;
	}
}

static t_path	*display_line(t_path **list, int tab[], int max_size, int n)
{
	int		k;
	t_path	*tmp;
	int		j;

	k = -1;
	tmp = NULL;
	while (*list && ++k < tab[0])
	{
		display_string((*list)->path, max_size, n);
		j = 1;
		delete_link(list, *list);
		while (*list && j < tab[1])
		{
			add_list(&tmp, (*list)->path);
			delete_link(list, *list);
			++j;
		}
	}
	return (tmp);
}

void			column_display(t_path **list, struct winsize w,
		int nbr_list, int n)
{
	int		max_size;
	int		tab[2];
	t_path	*tmp2;

	max_size = ft_size(*list, n);
	tab[0] = w.ws_col / (max_size + 1);
	tab[1] = nbr_list / tab[0];
	tab[1] += (nbr_list % tab[0]) ? 1 : 0;
	while (tab[1] > 0)
	{
		tmp2 = display_line(list, tab, max_size, n);
		delete_list(list);
		ft_printf("\n");
		*list = tmp2;
		--tab[1];
	}
	*list = NULL;
}
