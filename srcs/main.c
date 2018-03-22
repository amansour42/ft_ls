/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:18:43 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:49:52 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		check_flag(int ac, char **av, t_env *e)
{
	int i;
	int j;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				(av[i][j] == 'l') ? e->flag |= L : 0;
				(av[i][j] == 'a') ? e->flag |= A : 0;
				(av[i][j] == 'r') ? e->flag |= R : 0;
				(av[i][j] == 'R') ? e->flag |= BIGR : 0;
				(av[i][j] == 't') ? e->flag |= T : 0;
				(av[i][j] == '1') ? e->flag |= MINUS : 0;
			}
		}
		else
			add_list(&LIST, av[i]);
	}
}

int				main(int ac, char **av)
{
	t_env			e;
	t_path			*p;

	e.flag = 0;
	e.list = NULL;
	check_flag(ac, av, &e);
	if (!(e.list))
		add_list(&(e.list), ".");
	p = e.list;
	while (p)
	{
		ft_ls(e.flag, p->path);
		p = p->next;
	}
	delete_list(&(e.list));
	return (0);
}
