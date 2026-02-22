/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 03:17:30 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/22 20:16:39 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->arg_cmd[0], "cd", 3) == 0)
		data->last_exit_code = ft_cd(data, cmd->arg_cmd);
	else if (ft_strncmp(cmd->arg_cmd[0], "echo", 5) == 0)
		data->last_exit_code = ft_echo(cmd);
	else if (ft_strncmp(cmd->arg_cmd[0], "env", 4) == 0)
		data->last_exit_code = ft_env(data);
	else if (ft_strncmp(cmd->arg_cmd[0], "exit", 5) == 0)
		data->last_exit_code = ft_exit(cmd, data);
	else if (ft_strncmp(cmd->arg_cmd[0], "export", 7) == 0)
		data->last_exit_code = ft_export(data, cmd->arg_cmd);
	else if (ft_strncmp(cmd->arg_cmd[0], "pwd", 4) == 0)
		data->last_exit_code = ft_pwd(data);
	else if (ft_strncmp(cmd->arg_cmd[0], "unset", 6) == 0)
		data->last_exit_code = ft_unset(data, cmd->arg_cmd);
	return (0);
}
