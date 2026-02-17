/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 15:01:34 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;
	t_data	*data;

	if (ac >= 2)
		return (0);
	data = make_my_env(env);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		token = lexer(line);
		print_tokens(token); // DEBUG
		cmd = parsing(token, data);
		print_cmd(cmd); // DEBUG
		// print_env(data); // DEBUG
		// EXEC
		exec_cmd(cmd);
		add_history(line);
		// CLEAN
		free_cmd(cmd);
		free(line);
	}
	//rl_clear_history();
	return (0);
}
