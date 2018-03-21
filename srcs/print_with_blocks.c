#include "ft_ls.h"

static int          length_nbr(long long nbr)
{
    int nb;

    nb = 1;
    while (nbr / 10)
    {
        ++nb;
        nbr /= 10;
    }
    return (nb);
}

static int          big_nlink(t_path *list)
{
    struct stat sb;
    t_path      *tmp;
    int         big;

    tmp = list;
    big = 0;
    while (tmp)
    {
        if (lstat(tmp->path, &sb) == -1)
        {
            perror("stat");
            exit(0);
        }
        (sb.st_nlink > big) ? big =  sb.st_nlink : 0; 
        tmp = tmp->next;
    }
    return (length_nbr(big));
}

static long long    big_size(t_path *list)
{
    struct stat     sb;
    t_path          *tmp;
    long long       big;

    tmp = list;
    big = 0;
    while (tmp)
    {
        if (lstat(tmp->path, &sb) == -1)
        {
            perror("stat");
            exit(0);
        }
        (sb.st_size > big) ? big =  sb.st_size : 0; 
        tmp = tmp->next;
    }
    return (length_nbr(big));
}

static void         special_print(long long nbr, int len)
{
    int i;

    i = len - length_nbr(nbr) + 1;
    while (i)
    {
        ft_printf(" ");
        --i;
    }
    ft_printf("%lld", nbr);
}

void                print_with_blocks(t_path *list, char *str)
{
    struct stat buffer;
    t_path      *tmp;
    int         nbr_nlink;
    int         nbr_size;

    tmp = list;
    nbr_nlink = big_nlink(list);
    nbr_size = big_size(list);
    total(list);
    while (tmp)
    {
        lstat(tmp->path, &buffer);
        type(buffer);
        rights(buffer);
        special_print(buffer.st_nlink, nbr_nlink);
        ft_printf(" %s  %s ", getpwuid(buffer.st_uid)->pw_name, getgrgid(buffer.st_gid)->gr_name);
        special_print(buffer.st_size, nbr_size);
        ft_printf(" %.12s %s", (ctime(&buffer.st_mtime)) + 4, (tmp->path) + ft_strlen(str));
        (S_ISLNK(buffer.st_mode) == 1) ? print_link(tmp->path, buffer) : ft_printf("\n");
        tmp = tmp->next;
    }
}