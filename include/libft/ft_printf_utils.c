/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:06:18 by acesar-m          #+#    #+#             */
/*   Updated: 2025/08/24 18:06:29 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	print_base(long long n, char *base, int div)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0 && div == 10)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= div)
		count += print_base(n / div, base, div);
	c = base[n % div];
	count += print_char(c);
	return (count);
}

int	print_point(unsigned long p)
{
	int		i;
	int		count;
	char	*base;
	char	str[17];

	i = 0;
	count = 0;
	base = "0123456789abcdef";
	if (!p || p == 0)
		return (print_str("(nil)"));
	count = print_str("0x");
	while (p > 0)
	{
		str[i] = base[p % 16];
		p /= 16;
		i++;
	}
	count += i;
	i--;
	while (i >= 0)
		write (1, &str[i--], 1);
	return (count);
}