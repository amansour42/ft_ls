/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:18:43 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 09:03:53 by amansour         ###   ########.fr       */
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
				if (av[i][j] == 'l')
					e->flag |= L;
				else if (av[i][j] == 'a')
					e->flag |= A;
				else if (av[i][j] == 'r')
					e->flag |= R;
				else if (av[i][j] == 'R')
					e->flag |= BIGR;
				else if (av[i][j] == 't')
					e->flag |= T;
				else if (av[i][j] == '1')
					e->flag |= MINUS;
			}
		}
		else
			add_list(&LIST, av[i]);
	}
}

int	main(int ac, char **av)
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
	while (1)
		;
	return (0);
}
