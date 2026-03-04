/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/04 16:17:13 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	helper_main(t_data *data)
{
	free_data(data);
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;
	t_data	*data;
	int		shell;

	if (ac >= 2)
		return (0);
	shell = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	data = make_my_env(env);
	while (1)
	{
		if (shell)
			interactive_signals_management();
		if (shell)
			line = readline(PROMPT);
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		token = lexer(line, data);
		print_tokens(token);
		cmd = parsing(token, data);
		print_cmd(cmd);
		exec_cmd(cmd, data);
		if (shell && line[0])
			add_history(line);
		free_cmd(cmd);
		free(line);
	}
	helper_main(data);
	return (0);
}
