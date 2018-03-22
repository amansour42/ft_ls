/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:24:32 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 10:24:35 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		clean_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}

static int	month(char *str)
{
	if (!ft_strcmp(str, "Jan"))
		return (1);
	if (!ft_strcmp(str, "Feb"))
		return (2);
	if (!ft_strcmp(str, "Mar"))
		return (3);
	if (!ft_strcmp(str, "Apr"))
		return (4);
	if (!ft_strcmp(str, "Mai"))
		return (5);
	if (!ft_strcmp(str, "Jun"))
		return (6);
	if (!ft_strcmp(str, "Jul"))
		return (7);
	if (!ft_strcmp(str, "Aug"))
		return (8);
	if (!ft_strcmp(str, "Sep"))
		return (9);
	if (!ft_strcmp(str, "Oct"))
		return (10);
	if (!ft_strcmp(str, "Nov"))
		return (11);
	return (12);
}

static int	compare_hour(char *s1, char *s2)
{
	char	**str1;
	char	**str2;
	int		res;

	str1 = ft_strsplit(s1, ':');
	str2 = ft_strsplit(s2, ':');
	if (!(res = ft_atoi(str1[0]) - ft_atoi(str2[0])))
		if (!(res = ft_atoi(str1[1]) - ft_atoi(str2[1])))
			res = ft_atoi(str1[2]) - ft_atoi(str2[2]);
	clean_split(str1);
	clean_split(str2);
	return (res);
}

static int	compare_time(char *s1, char *s2)
{
	char		**str1;
	char		**str2;
	int			res;
	struct stat	sb;

	if (stat(s1, &sb) == -1)
		error("stat");
	str1 = ft_strsplit(ctime(&sb.st_mtime), ' ');
	if (stat(s2, &sb) == -1)
		error("stat");
	str2 = ft_strsplit(ctime(&sb.st_mtime), ' ');
	if (!(res = ft_atoi(str1[4]) - ft_atoi(str2[4])))
		if (!(res = month(str1[1]) - month(str2[1])))
			if (!(res = ft_atoi(str1[2]) - ft_atoi(str2[2])))
				res = compare_hour(str1[3], str2[3]);
	clean_split(str1);
	clean_split(str2);
	return (res);
}

void		time_listing(t_path **list)
{
	t_path *res;
	t_path *ptmp;
	t_path *tmp;

	res = NULL;
	while (*list)
	{
		ptmp = *list;
		tmp = (*list)->next;
		while (tmp)
		{
			if (compare_time(tmp->path, ptmp->path) > 0)
				ptmp = tmp;
			tmp = tmp->next;
		}
		add_list(&res, ptmp->path);
		delete_link(list, ptmp);
	}
	*list = res;
}
