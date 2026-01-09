/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 01:37:17 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/20 09:31:07 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned(n / 10);
	count += ptf_putchar_fd((n % 10) + '0', 1);
	return (count);
}

int	ft_putpointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += ft_puthex((unsigned long)ptr);
	return (count);
}

int	ptf_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ptf_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		s = "(null)";
	len = ft_strlen_printf(s);
	return (write(fd, s, len));
}

int	ptf_putnbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ptf_putchar_fd('-', 1);
		n = -n;
	}
	if (n >= 10)
		count += ptf_putnbr(n / 10);
	count += ptf_putchar_fd((n % 10) + '0', 1);
	return (count);
}
