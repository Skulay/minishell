/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 18:24:20 by alehamad         ###   ########.fr       */
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
		// print_tokens(token); // DEBUG
		cmd = parsing(token, data);
		// print_cmd(cmd); // DEBUG
		// print_env(data); // DEBUG
		// ft_export(data); // TEST EXPORT
		// EXEC
		if (cmd && cmd->arg_cmd && cmd->arg_cmd[0])
		{
			if (is_builtin(cmd->arg_cmd[0]))
				exec_builtin(cmd, data);
		}
		else
			exec_cmd(cmd, data);
		add_history(line);
		// CLEAN
		free_cmd(cmd);
		free(line);
	}
	free_tab(data->my_env);
	rl_clear_history();
	return (0);
}
