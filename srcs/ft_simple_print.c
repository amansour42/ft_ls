/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:31:48 by amansour          #+#    #+#             */
/*   Updated: 2018/01/29 11:27:17 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path		*files(char *str)
{
	DIR				    *dir;
	struct dirent	*flow;
	t_path			  *files;

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

static void		list_to_print(t_path **l)
{
	t_path *tmp;
	t_path *new;

	tmp = *l;
	new = NULL;
	while (tmp)
	{
		if (tmp->path[0] != '.')
			add_list(&new, tmp->path);
		tmp = tmp->next;
	}
	delete_list(l);
	*l = new;
}

void		print_list(int flag, char *str)
{
	t_path	  		*path;
	t_path			*tmp;
	struct winsize 	w;

	if (!(path = files(str)))
		return ;
  	if (flag & R)
		reverse_list(&path);
	else if (flag & T)
		time_listing(&path);
	if ((flag & A) == 0)
		list_to_print(&path);
	str = ft_strjoin(str, "/");
	if (flag & L)
	{
		//printf("%s", path->path);
		print_with_blocks(path, str);
	}
	else if (isatty(STDOUT_FILENO))
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		column_display(path, w, length_list(path));
	}
	else
    {
		tmp = path;
        while (tmp->next!=NULL)
        {
            ft_printf("%s\n", tmp->path);
            tmp = tmp->next;
        }
        ft_printf("%s\n", tmp->path);
    }
}
