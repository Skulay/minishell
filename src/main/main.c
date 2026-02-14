/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/14 18:44:21 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size == 0)
	{
		return (j);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

static int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && is_set(s1[j - 1], set))
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, j - i + 1);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_get_prompt(char **env)
{
	char	*prompt;
	char	*name;
	char	*path;

	name = getenv("USER");
	if (!name)
		name = "minishell";
	path = getenv("PWD");
	if (!path)
	{
		path = getcwd(path, 10);
		return (path);
	}
	if (ft_strncmp(path, "/home\0", 6))
	{
		path = ft_strtrim(path, "/home");
		path = ft_strtrim(path, name);
		prompt = ft_strjoin(name, " ~");
		prompt = ft_strjoin(prompt, path);
	}
	else
		prompt = "/";
	prompt = ft_strjoin(prompt, " >");
	return (prompt);
}

char	**make_env(void)
{
	char **env;

	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env[0] = getcwd(NULL, 50);
	env[1] = "PATH=";
	env[2] = NULL;
	return (env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;

	if (ac >= 2)
		return (0);
	if (!env[0])
		env = make_env();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break;
		token = lexer(line);
		print_tokens(token);
		add_history(line);
		// fonction a faire pour execve(line);
		free(line);
	}
	clear_history();
	return(0);
}
