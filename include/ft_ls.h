/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:00:16 by amansour          #+#    #+#             */
/*   Updated: 2018/01/26 16:48:24 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define FLAG		"lRrat"
# define L			0x01
# define A			0x02
# define R			0x04
# define BIGR		0x08
# define T			0x10
# define LIST		e->list
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>
# include <grp.h>
# include <pwd.h>
# include "../libft/libft.h"
# include "../libprint/includes/ft_printf.h"

typedef struct		s_path
{
	char			*path;
	char			*type;
	long			inoeud;
	long			links;
	unsigned long	mode;
	char			*owner;
	char			*group;
	long long		blocs;
	long long		size;
	time_t			last_access;
	time_t			last_mod;
	time_t			time;
	struct s_path	*next;
}					t_path;

typedef struct		s_env
{
	int				flag;
	t_path			*list;
}					t_env;

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

/*
** L
*/
void				print_list(int flag, char *str);
void				print_recursive(int flag, char *str);
void				print_without_blocs(int flag, char *str);
void        		print_with_blocks(t_path *list, char *str);
/*
** treatement
*/
void				reverse_list(t_path **list);
void				time_listing(t_path **list);
void				copy_data(t_path **path, t_path *to_copy);
void				delete_link(t_path **path, t_path *to_delete);

/*
** sorting
*/

void				sort(t_path **list);

/*
** display columns
*/
void    			column_display(t_path **list, struct winsize w, int nbr_list, int n);
/*
** print_blocks
*/
void				type(struct stat buffer);
void				rights(struct stat buffer);
void   				print_link(char *s2, struct stat buffer);
void     			total(t_path *list);
#endif
