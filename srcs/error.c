/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 09:09:44 by amansour          #+#    #+#             */
/*   Updated: 2018/03/26 09:10:15 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(t_path *p)
{
	t_path *tmp;

	sort(&p);
	tmp = p;
	while (tmp)
	{
		ft_printf("ls: %s: No such file or directory\n", tmp->path);
		tmp = tmp->next;    
	}
	delete_list(&tmp);
}

void	error(char *str, t_path **p)
{
	if (p)
		delete_list(p);
	perror(str);
	exit(0);
}
