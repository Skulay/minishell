/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:15:57 by alehamad          #+#    #+#             */
/*   Updated: 2025/12/15 20:17:44 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_spaces(const char **s)
{
	while (**s == ' ' || (**s >= 9 && **s <= 13))
		(*s)++;
}

double	ft_atod(const char *s)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 1.0;
	skip_spaces(&s);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1.0;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10.0 + (*s++ - '0');
	if (*s++ == '.')
	{
		while (*s >= '0' && *s <= '9')
		{
			frac *= 0.1;
			result += (*s++ - '0') * frac;
		}
	}
	return (result * sign);
}
