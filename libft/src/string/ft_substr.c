/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:52:46 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/10 21:41:55 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	s_len;

	if (!s)
		return (malloc(1));
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dst = malloc(1);
		if (!dst)
			return (0);
		dst[0] = '\0';
		return (dst);
	}
	if (len > s_len - start)
		len = s_len - start;
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, s + start, len + 1);
	return (dst);
}
