/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/28 06:32:44 by alehamad         ###   ########.fr       */
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
		interactive_signals_management();
		line = readline(PROMPT);
		if (!line)
			break ;
		token = lexer(line, data);
		cmd = parsing(token, data);
		if (cmd && cmd->arg_cmd && cmd->arg_cmd[0])
			exec_cmd(cmd, data);
		if (line[0])
			add_history(line);
		free_cmd(cmd);
		free(line);
	}
	free_data(data);
	rl_clear_history();
	return (0);
}
