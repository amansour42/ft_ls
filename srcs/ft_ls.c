/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:53:36 by amansour          #+#    #+#             */
/*   Updated: 2018/01/29 13:54:13 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_path  *files(char *str)
{
  DIR           *dir;
  struct dirent *flow;
  t_path        *files;
  char          *s;

  files = NULL;
  s = ft_strjoin(str, "/");
  if ((dir = opendir(str)))
    while ((flow = readdir(dir)))
    {
      if (ft_strcmp(flow->d_name, ".") && ft_strcmp(flow->d_name, ".."))
          add_list(&files, flow->d_name); //ft_strjoin(s, flow->d_name));
      //else 
      //    add_list(&files, flow->d_name);
    }
  sort(&files);
  return (files);
}

void	ft_ls(int flag, char *str)
{
  t_path  *path;
  t_path  *tmp;

	print_list(flag, str);
  if (flag & BIGR)
  {
    path = files(str);
    if (!path)
      return ;
    tmp = path;
    while (tmp)
    {
      while (tmp && (!opendir(tmp->path)))//|| !ft_strcmp(tmp->path, "..") || !ft_strcmp(tmp->path, ".")))
        tmp = tmp->next;
      if (tmp)
      {
        ft_printf("%s:\n", tmp->path);
        ft_ls(flag, tmp->path);
        tmp = tmp->next;
      }
    }
  }
}
