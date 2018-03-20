/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:25:05 by amansour          #+#    #+#             */
/*   Updated: 2018/01/26 16:52:56 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void  attribut(t_path *path)
{
  struct stat   sb;

  if (stat(path->path, &sb) == -1)
  {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  //type(sb, &(path->type)); 
  path->inoeud = (long)sb.st_ino;
  path->mode = (unsigned long)sb.st_mode;
  path->links = sb.st_nlink;
  path->owner = getpwuid(sb.st_uid)->pw_name;
  path->group = getgrgid(sb.st_gid)->gr_name;
  path->blocs = (long) sb.st_blocks;
  path->size = (long long) sb.st_size;
  path->last_access = sb.st_mtime;
  path->last_mod = sb.st_ctime;
  path->time = sb.st_ctime;
}

void        all_attribut(t_path **p)
{
  t_path *tmp;

  tmp = *p;
  while (tmp)
  {
    attribut(tmp);
    tmp = tmp->next;
  }
}