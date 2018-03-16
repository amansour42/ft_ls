
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

static void    display_string(char *str, int max_size)
{
    int h;

    ft_printf("%s", str);
    h = ft_strlen(str);
    while (h < max_size + 7)
    {
        ft_printf(" ");
        h++;
    }
}
void    column_display(t_path *list, struct winsize w, int nbr_list)
{
    int     max_size;
    int     nbr_column;
    int     nbr_line;
    t_path  *tmp;
    t_path  *tmp2;
    int     i;
    int     j;
    int     k;

    max_size = ft_size(list);
    nbr_column = w.ws_col / (max_size + 10);
    nbr_line = nbr_list / nbr_column;
    nbr_line += (nbr_list % nbr_column) ? 1 : 0;
    printf("NBR LINE ==>%d\n", nbr_column);
    i = -1;
    tmp = list;
    while(++i < nbr_line - 1)
    {
        tmp2 = NULL;
        k = -1;
        while (++k < nbr_column && tmp)
        {
            display_string(tmp->path, max_size);
            j = 1;
            tmp = tmp->next;
            while (tmp && j < nbr_line)
            {
                add_list(&tmp2, tmp->path);
                tmp = tmp->next;
                ++j;
            }
        }
        delete_list(&tmp);
        printf("\n");
        tmp = tmp2;
    }
    //tmp2 = tmp;
    while (tmp)
    {
        display_string(tmp->path, max_size);
        tmp = tmp->next;
    }
    printf("\n");
}