/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:06:45 by amansour          #+#    #+#             */
/*   Updated: 2017/12/05 12:43:38 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		length_base(uintmax_t nbr, int base)
{
	int len;

	len = 1;
	while ((nbr /= base))
		++len;
	return (len);
}

char	*nbr_to_string(uintmax_t value, int len, int base)
{
	char	*str;
	char	*s;

	s = "0123456789abcdef";
	if (base < 0)
	{
		s = "0123456789ABCDEF";
		base = -base;
	}
	str = (char *)malloc(len + 1);
	str[len] = '\0';
	str[--len] = s[value % base];
	while ((value /= base))
		str[--len] = s[value % base];
	while (--len >= 0)
		str[len] = '0';
	return (str);
}
