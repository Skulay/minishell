/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:47:55 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/20 09:31:26 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_format(char format, va_list args)
{
	if (format == 'c')
		return (ptf_putchar_fd(va_arg(args, int), 1));
	if (format == 's')
		return (ptf_putstr_fd(va_arg(args, char *), 1));
	if (format == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	if (format == 'd' || format == 'i')
		return (ptf_putnbr(va_arg(args, int)));
	if (format == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (format == 'x')
		return (ft_puthex(va_arg(args, unsigned int)));
	if (format == 'X')
		return (ft_putbighex(va_arg(args, unsigned int)));
	if (format == '%')
		return (ptf_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!str)
		return (0);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += handle_format(str[i + 1], args);
			i++;
		}
		else
			count += ptf_putchar_fd(str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
