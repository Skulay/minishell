/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:07:43 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/12 17:30:49 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	helper_main(t_data *data)
{
	free_data(data);
	rl_clear_history();
}

void	shell_loop(t_data *data, int shell)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

	while (1)
	{
		if (shell)
		{
			interactive_signals_management();
			line = readline(PROMPT);
			if (g_sig_code == 130)
			{
				data->last_exit_code = 130;
				g_sig_code = 0;
			}
		}
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
		}
		if (!line)
			break ;
		if (shell && line[0])
			add_history(line);
		token = lexer(line, data);
		cmd = parsing(token, data);
		exec_cmd(cmd, data);
		free_cmd(cmd);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;
	t_data	*data;
	int		shell;

	if (ac >= 2)
		return (1);
	shell = isatty(STDIN_FILENO);
	data = make_my_env(env);
	shell_loop(data, shell);
	helper_main(data);
	return (data->last_exit_code);
}
