/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:40:11 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/09 18:06:58 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	len = ft_strlen(str) - 1;
	i = 0;
	if (!str)
		return ;
	if (str[0] == '-')
		i++;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
}

static int	ft_intlen(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		i;
	long	nb;

	i = 0;
	nb = n;
	dst = malloc(sizeof(char) * (ft_intlen(n) + 1));
	if (!dst)
		return (NULL);
	if (nb == 0)
		dst[i++] = '0';
	if (nb < 0)
	{
		dst[i++] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		dst[i++] = (nb % 10) + '0';
		nb = nb / 10;
	}
	dst[i] = '\0';
	ft_strrev(dst);
	return (dst);
}
