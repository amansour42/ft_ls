/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:37:19 by amansour          #+#    #+#             */
/*   Updated: 2017/12/06 10:49:30 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>


int	main(int ac, char **av)
{
	DIR				*dir;
	struct dirent	*flux;

	if ((dir = opendir(av[1])))
	{
		while ((flux = readdir(dir)))
			printf("NAME FILE = %s\n", flux->d_name);
		closedir(dir);
	}
	else
		perror("ERROR");
	return (0);
}
