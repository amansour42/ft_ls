/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:59:43 by amansour          #+#    #+#             */
/*   Updated: 2017/12/05 12:45:35 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		flag(char **str)
{
	int nbr;

	nbr = 0;
	while (**str && belong("#- +0", **str))
	{
		if (**str == '#')
			nbr |= ALTFLAG;
		else if (**str == '-')
			nbr |= LEFTFORMATFLAG;
		else if (**str == '+')
			nbr |= SHOWSIGNFLAG;
		else if (**str == ' ')
			nbr |= SPACEFLAG;
		else
			nbr |= LEADZEROFLAG;
		++(*str);
	}
	return (nbr);
}

int		modifier(char **str)
{
	int nbr;

	nbr = 0;
	while (**str && belong("lLhjz", **str))
	{
		if (**str == 'l' && (nbr & LONGMOD))
			nbr |= LONGLONGMOD;
		else if (**str == 'l')
			nbr |= LONGMOD;
		else if (**str == 'L')
			nbr |= LONGDOUBLEMOD;
		else if (**str == 'h' && (nbr & HALFMOD))
			nbr |= HALFHALFMOD;
		else if (**str == 'h')
			nbr |= HALFMOD;
		else if (**str == 'z')
			nbr |= SIZETMOD;
		else if (**str == 'j')
			nbr |= MAXMOD;
		++(*str);
	}
	return (nbr);
}

int		string_to_int(char **str)
{
	int nbr;

	nbr = 0;
	while (**str && ft_isdigit(**str))
	{
		nbr = nbr * 10 + (**str - '0');
		++(*str);
	}
	return (nbr);
}
