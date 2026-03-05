/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 03:53:22 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/04 00:55:18 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static int	is_vstart(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_')
		return (1);
	return (0);
}

static int	is_vchar(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static char	*join_char(char *s, char c)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

char	*ft_heredoc_expand(char *line)
{
	char	*result;
	char	*var;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && is_vstart(line[i + 1]))
		{
			start = ++i;
			while (line[i] && is_vchar(line[i]))
				i++;
			var = ft_substr(line, start, i - start);
			result = ft_strjoin_free(result, getenv(var));
			if (!getenv(var))
				result = ft_strjoin_free(result, "");
			free(var);
		}
		else
			result = join_char(result, line[i++]);
	}
	free(line);
	return (result);
}
