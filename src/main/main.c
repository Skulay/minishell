/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 07:00:03 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

	if (ac >= 2)
		return (0);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		token = lexer(line);
		print_tokens(token); // DEBUG
		cmd = parsing(token);
		print_cmd(cmd); // DEBUG
		// EXEC
		add_history(line);
		// CLEAN
		free_cmd(cmd);
		free(line);
	}
	clear_history();
	return (0);
}
