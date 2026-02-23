/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:34:25 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/23 03:38:05 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	isabsolute(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

char	*getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}

char	*testpath(char **paths, char *binary)
{
	int		i;
	char	*part;
	char	*full;

	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		full = ft_strjoin(part, binary);
		free(part);
		if (access(full, F_OK | X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*findvalidpath(char **env, char *binary)
{
	char	*path;
	char	**paths;

	if (!binary || *binary == '\0')
		return (NULL);
	if (isabsolute(binary))
	{
		if (access(binary, F_OK | X_OK) == 0)
			return (ft_strdup(binary));
		return (NULL);
	}
	path = getpath(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	path = testpath(paths, binary);
	free_tab(paths);
	return (path);
}
