#include "ft_ls.h"

void    print_error(t_path *p)
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

void	error(char *str)
{
	perror(str);
	exit(0);
}