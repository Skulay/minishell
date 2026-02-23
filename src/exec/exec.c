/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:47:02 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/23 23:11:37 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_cmd(t_cmd *command, t_data *data)
{
	int	stdin_original;
	int	stdout_original;

	if (!command || !command->arg_cmd || !command->arg_cmd[0])
		return (0);
	if (!command->next && is_builtin(command->arg_cmd[0]))
	{
		stdin_original = dup(STDIN_FILENO);
		stdout_original = dup(STDOUT_FILENO);
		if (redirection_manager(command->redir) != 0)
		{
			data->last_exit_code = 1;
			return (1);
		}
		exec_builtin(command, data);
		dup2(stdin_original, STDIN_FILENO);
		dup2(stdout_original, STDOUT_FILENO);
		close(stdin_original);
		close(stdout_original);
		return (0);
	}
	execute_pipeline(command, data);
	return (0);
}
