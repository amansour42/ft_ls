
#include "ft_ls.h"

static int		ft_size(t_path *l)
{
	int		  i;
	int		  j;
	t_path	*tmp;

	tmp = l;
	i = ft_strlen(l->path);
	while(tmp)
	{
		j = ft_strlen(tmp->path);
		tmp = tmp->next;
		if (j > i)
			i = j;
	}
	return (i);
}

static void    display_string(char *str, int max_size, int n)
{
    int h;

    ft_printf("%s", str + n);
    h = ft_strlen(str) - n;
    while (h < max_size + 7)
    {
        ft_printf(" ");
        h++;
    }
}
void    column_display(t_path *list, struct winsize w, int nbr_list, int n)
{
    int     max_size;
    int     nbr_column;
    int     nbr_line;
    t_path  *tmp2;
    int     i;
    int     j;
    int     k;

    max_size = ft_size(list);
    nbr_column = w.ws_col / (max_size + 6);
    nbr_line = nbr_list / nbr_column;
    nbr_line += (nbr_list % nbr_column) ? 1 : 0;
    i = -1;
    while(nbr_line)
    {
        tmp2 = NULL;
        k = -1;
        while (++k < nbr_column && list)
        {
            display_string(list->path, max_size, n);
            j = 1;
            delete_link(&list, list);
            while (list && j < nbr_line)
            {
                add_list(&tmp2, list->path);
                delete_link(&list, list);
                ++j;
            }
        }
        delete_list(&list);
        printf("\n");
        list = tmp2;
        nbr_line--;
    }
}