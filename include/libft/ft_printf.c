/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:04:17 by acesar-m          #+#    #+#             */
/*   Updated: 2025/08/24 18:05:44 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_format(char spec, va_list args)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count = print_char(va_arg(args, int));
	else if (spec == 's')
		count = print_str(va_arg(args, char *));
	else if (spec == 'd' || spec == 'i')
		count = print_base(va_arg(args, int), "0123456789", 10);
	else if (spec == 'u')
		count = print_base(va_arg(args, unsigned int), "0123456789", 10);
	else if (spec == 'x')
		count = print_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
	else if (spec == 'X')
		count = print_base(va_arg(args, unsigned int), "0123456789ABCDEF", 16);
	else if (spec == 'p')
		count = print_point(va_arg(args, unsigned long));
	else if (spec == '%')
		count = print_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += check_format(str[i], args);
		}
		else
			count += print_char(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}