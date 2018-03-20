#include "ft_ls.h"

static char   *print_rights(struct stat buffer)
{
    char *chaine_droits;
    
    chaine_droits = (char*)malloc(sizeof(char) * 11);
    ft_strcpy(chaine_droits, "----------");
    if (S_ISLNK(buffer.st_mode) == 1) chaine_droits[0]='l';
    if (S_ISDIR(buffer.st_mode) == 1) chaine_droits[0]='d';
    if (S_ISBLK(buffer.st_mode) == 1) chaine_droits[0]='b';
	if (S_ISCHR(buffer.st_mode) == 1) chaine_droits[0]='c';
	if (S_ISFIFO(buffer.st_mode) == 1) chaine_droits[0]='f';
	if (S_ISSOCK(buffer.st_mode) == 1) chaine_droits[0]='s';
    if ((buffer.st_mode & S_IRUSR) == S_IRUSR) chaine_droits[1]='r';
    if ((buffer.st_mode & S_IWUSR) == S_IWUSR) chaine_droits[2]='w';
    if ((buffer.st_mode & S_IXUSR) == S_IXUSR) chaine_droits[3]='x';
    if ((buffer.st_mode & S_IRGRP) == S_IRGRP) chaine_droits[4]='r';
    if ((buffer.st_mode & S_IWGRP) == S_IWGRP) chaine_droits[5]='w';
    if ((buffer.st_mode & S_IXGRP) == S_IXGRP) chaine_droits[6]='x';
    if ((buffer.st_mode & S_IROTH) == S_IROTH) chaine_droits[7]='r';
    if ((buffer.st_mode & S_IWOTH) == S_IWOTH) chaine_droits[8]='w';
    if ((buffer.st_mode & S_IXOTH) == S_IXOTH) chaine_droits[9]='x';
    return (chaine_droits);
}

void                 sum(t_path *list)
{
    struct stat      sb;
    t_path           *tmp;
    long long        big;

    tmp = list;
    big = 0;
    while (tmp)
    {
        if (ft_strcmp(tmp->path, ".") != 0 && ft_strcmp(tmp->path, "..") != 0) 
        {
            lstat(tmp->path, &sb);//a revoir lstat ou stat
            big += sb.st_blocks; 
        }
        tmp = tmp->next;
    }
    ft_printf("total %lld\n", big);
}
int                 length_nbr(long long nbr)
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

static int  big_nlink(t_path *list)
{
    struct stat sb;
    t_path      *tmp;
    int         big;

    tmp = list;
    big = 0;
    while (tmp)
    {
        stat(tmp->path,&sb);
        (sb.st_nlink > big) ? big =  sb.st_nlink : 0; 
        tmp = tmp->next;
    }
    return (length_nbr(big));
}

static long long    big_size(t_path *list)
{
    struct stat     sb;
    t_path          *tmp;
    long long        big;

    tmp = list;
    big = 0;
    while (tmp)
    {
        stat(tmp->path,&sb);
        (sb.st_size > big) ? big =  sb.st_size : 0; 
        tmp = tmp->next;
    }
    return (length_nbr(big));
}

void                special_print(long long nbr, int len)
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

void                print_with_blocks(t_path *list)
{
    struct stat buffer;
    t_path      *tmp;
    int         nbr_nlink;
    int         nbr_size;

    tmp = list;
    nbr_nlink = big_nlink(list);
    nbr_size = big_size(list);
    sum(list);
    while (tmp)
    {
        stat(tmp->path,&buffer);
        ft_printf("%s ", print_rights(buffer));
        special_print(buffer.st_nlink, nbr_nlink);
        ft_printf(" %s  %s ", getpwuid(buffer.st_uid)->pw_name,
            getgrgid(buffer.st_gid)->gr_name);
        special_print(buffer.st_size, nbr_size);
        ft_printf(" %.12s %s\n", (ctime(&buffer.st_mtime)) + 4, tmp->path);
        tmp = tmp->next;
    }
}