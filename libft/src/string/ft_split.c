/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 06:06:40 by alehamad          #+#    #+#             */
/*   Updated: 2025/11/10 17:32:25 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static int	ft_strsize(char const *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_strlencpy(char *dest, char const *src, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

static void	ft_free(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		count;
	int		i;
	int		pos;

	if (!s)
		return (0);
	count = ft_count(s, c);
	strs = (char **)malloc((count + 1) * sizeof(char *));
	i = 0;
	pos = 0;
	if (!strs)
		return (NULL);
	while (i < count)
	{
		while (s[pos] == c)
			pos++;
		strs[i] = (char *)malloc((ft_strsize(&s[pos], c) + 1) * sizeof(char));
		if (!strs[i])
			return (ft_free(strs, (i - 1)), NULL);
		pos += ft_strlencpy(strs[i], &s[pos], ft_strsize(&s[pos], c));
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
