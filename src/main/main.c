/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/14 21:24:52 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
