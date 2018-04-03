/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:18:43 by amansour          #+#    #+#             */
/*   Updated: 2018/03/26 09:09:37 by amansour         ###   ########.fr       */
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

static int		treat_error(t_path **p)
{
	t_path		*tmp;
	t_path		*tmp2;
	struct stat	sb;
	t_path		*error;

	tmp = NULL;
	tmp2 = *p;
	error = NULL;
	while (tmp2)
	{
		(lstat(tmp2->path, &sb) == -1) ? add_list(&error, tmp2->path) :
			add_list(&tmp, tmp2->path);
		tmp2 = tmp2->next;
	}
	if (!error)
	{
		delete_list(&tmp);
		return (0);
	}
	delete_list(p);
	*p = tmp;
	print_error(error);
	return (1);
}

static void		print_right_way(t_path **path, int flag)
{
	sort(path);
	if ((flag & A) == 0)
		list_to_print(path);
	if (flag & R)
		reverse_list(path);
	else if (flag & T)
		time_listing(path);
	if (flag & L)
		print_with_blocks(*path, NULL);
	else
		print_minus_one(*path, NULL);
	delete_list(path);
}

static int		treat_file(t_path **p, int flag)
{
	t_path		*tmp;
	t_path		*tmp2;
	t_path		*file;
	struct stat	sb;

	tmp = NULL;
	file = NULL;
	tmp2 = *p;
	while (tmp2)
	{
		lstat(tmp2->path, &sb);
		if ((S_ISLNK(sb.st_mode) && (flag & L))
			|| (!S_ISDIR(sb.st_mode) && !S_ISLNK(sb.st_mode)))
			add_list(&file, tmp2->path);
		else
			add_list(&tmp, tmp2->path);
		tmp2 = tmp2->next;
	}
	delete_list(p);
	*p = tmp;
	if (!file)
		return (0);
	print_right_way(&file, flag);
	return (1);
}

int				main(int ac, char **av)
{
	t_env			e;
	t_path			*p;
	int				yes;

	e.flag = 0;
	e.list = NULL;
	check_flag(ac, av, &e);
	if (!(e.list))
		add_list(&(e.list), ".");
	if (!ft_strcmp((e.list)->path, "*"))
	{
		free(e.list->path);
		(e.list)->path = ft_strdup(".");
	}
	p = e.list;
	yes = treat_error(&p) + treat_file(&p, e.flag) + length_list(p) - 1;
	sort(&p);
	while (p)
	{
		(yes) ? ft_printf("\n%s:\n", p->path) : 0;
		ft_ls(e.flag, p->path);
		delete_link(&p, p);
	}
	return (0);
}
