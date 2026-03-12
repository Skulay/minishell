/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:47:02 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/12 20:57:52 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fd_manipulation(int stdin_original, int stdout_original)
{
	dup2(stdin_original, STDIN_FILENO);
	dup2(stdout_original, STDOUT_FILENO);
	close(stdin_original);
	close(stdout_original);
}

int	exec_cmd(t_cmd *command, t_data *data)
{
	int	stdin_original;
	int	stdout_original;

	if (!command || !command->arg_cmd || !command->arg_cmd[0])
		return (0);
	if (!command->next && is_builtin(command->arg_cmd[0])
		|| command->arg_cmd[0][0] == '\0')
	{
		stdin_original = dup(STDIN_FILENO);
		stdout_original = dup(STDOUT_FILENO);
		if (redirection_manager(command->redir, data) != 0)
		{
			fd_manipulation(stdin_original, stdout_original);
			data->last_exit_code = 1;
			return (1);
		}
		exec_builtin(command, data);
		fd_manipulation(stdin_original, stdout_original);
		return (0);
	}
	execute_pipeline(command, data);
	return (0);
}

void	command_not_found(t_cmd *command, t_data *data, int *fd)
{
	if (command->next)
		fd_closer(fd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->arg_cmd[0], 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(" command not found\n", 2);
	free_all(command, data);
	exit(127);
}
