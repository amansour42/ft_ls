/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 09:50:53 by amansour          #+#    #+#             */
/*   Updated: 2017/12/05 12:44:37 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		result;
	char	*s;

	s = ft_strdup(format);
	va_start(ap, format);
	result = prints(&ap, s);
	va_end(ap);
	free(s);
	return (result);
}

int		prints(va_list *ap, char *str)
{
	int n;

	n = 0;
	while (n != -1 && *str)
	{
		while (*str && *str != '%')
		{
			write(1, str, 1);
			++n;
			++str;
		}
		if (*str == '%')
			n = test(&str, ap, n);
	}
	return (n);
}

int		test(char **str, va_list *ap, int n)
{
	t_format	format;
	char		*s;

	format.width = 0;
	format.flag = 0;
	format.p = -1;
	format.mod = 0;
	if (!fill_format(str, &format, ap))
		return (n);
	if (format.c == 'n')
	{
		to_n(format, ap, n);
		return (n);
	}
	if (belong(CONV, format.c))
	{
		if (!(s = conversion(format, ap)))
			return (-1);
		return (n + display(s, format));
	}
	return (n + display(c_to_s(format.c), format));
}
