/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:53:46 by amansour          #+#    #+#             */
/*   Updated: 2017/12/06 14:32:29 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int	main(int ac, char **av)
{
	struct stat sb;

	if (ac != 2) {
	printf("Usage: %s <pathname>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (stat(av[1], &sb) == -1) {
		perror("stat");
		return (0);
	}
	printf("Type de fichier :                 ");
	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("périphérique de bloc\n");      break;
		case S_IFCHR:  printf("périphérique de caractère\n"); break;
		case S_IFDIR:  printf("répertoire\n");                break;
		case S_IFIFO:  printf("FIFO/tube\n");                 break;
		case S_IFLNK:  printf("lien symbolique\n");           break;
		case S_IFREG:  printf("fichier ordinaire\n");         break;
		case S_IFSOCK: printf("socket\n");                    break;
		default:       printf("inconnu ?\n");                 break;
	}
	printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);
	printf("Mode :                             %lo (octal)\n", (unsigned long) sb.st_mode);
	printf("Nombre de liens :                  %ld\n", (long) sb.st_nlink);
	printf("Propriétaires :                    UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	printf("Taille de bloc d’E/S :             %ld octets\n", (long) sb.st_blksize);
	printf("Taille du fichier :                %lld octets\n", (long long) sb.st_size);
	printf("Blocs alloués :                    %lld\n", (long long) sb.st_blocks);
	printf("Dernier changement d’état :        %s", ctime(&sb.st_ctime));
	printf("Dernier accès au fichier :         %s", ctime(&sb.st_atime));
	printf("Dernière modification du fichier:  %s", ctime(&sb.st_mtime));
	return (0);
}
