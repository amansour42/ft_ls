/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:00:16 by amansour          #+#    #+#             */
/*   Updated: 2018/03/22 12:53:46 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define FLAG		"lRrat1"
# define L			0x01
# define A			0x02
# define R			0x04
# define BIGR		0x08
# define T			0x10
# define MINUS		0x20
# define LIST		e->list
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../libprint/includes/ft_printf.h"

typedef struct		s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_env
{
	int				flag;
	t_path			*list;
}					t_env;

typedef struct		s_deice
{
	int				maj;
	int				min;
	int				big;
	int				link;
	int				usr;
	int				grp;
}					t_device;

int					main(int ac, char **av);

/*
** ft_ls
*/
void				ft_ls(int flag, char *path);
/*
** list
*/

void				add_list(t_path **p, char *str);
void				delete_list(t_path **p);
int					length_list(t_path *path);
void				list_to_path(t_path **list, char *str);

/*
** L
*/
void				print_list(int flag, char *str);
void				print_recursive(int flag, char *str);
void				print_without_blocs(int flag, char *str);
void				print_with_blocks(t_path *list, char *str);
/*
** treatement
*/
void				reverse_list(t_path **list);
void				time_listing(t_path **list);
void				list_to_print(t_path **path);
void				print_minus_one(t_path *path, char *s);
void				delete_link(t_path **path, t_path *to_delete);
/*
** sorting
*/
void				sort(t_path **list);
/*
** print_blocks
*/
void				type(struct stat buffer);
void				rights(struct stat buffer);
void				llink(char *s2);
void				total(t_path *list);
void				special_print_2(long long nbr, int len);
void				special_print(struct stat info, t_device d);
void				print_usr_grp(struct stat sb, t_device d);
int					length_nbr(long long nbr);
/*
** error
*/
void				print_error(t_path *p);
void				error(char *str, t_path **p);
#endif
