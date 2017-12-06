/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:53:36 by amansour          #+#    #+#             */
/*   Updated: 2017/12/06 15:59:26 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(int flag, char *str)
{
	/*if (flag & L)
		print_with_blocs(flag, str);
	else if (flag & R)
		print_recursive(flag, str);
	else*/
		print_without_blocs(flag, str);
}
