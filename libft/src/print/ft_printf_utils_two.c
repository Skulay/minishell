/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:10:34 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/20 09:29:59 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_printf(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_puthex(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n == 0)
	{
		count += ptf_putchar_fd('0', 1);
		return (count);
	}
	if (n >= 16)
		count += ft_puthex(n / 16);
	count += ptf_putchar_fd(base[n % 16], 1);
	return (count);
}

int	ft_putbighex(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789ABCDEF";
	if (n == 0)
	{
		count += ptf_putchar_fd('0', 1);
		return (count);
	}
	if (n >= 16)
		count += ft_putbighex(n / 16);
	count += write(1, &base[n % 16], 1);
	return (count);
}
