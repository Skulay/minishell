/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 03:17:30 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/22 03:26:00 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->arg_cmd[0], "cd", 3) == 0)
		ft_cd(data, cmd->arg_cmd[1]);
	if (ft_strncmp(cmd->arg_cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	if (ft_strncmp(cmd->arg_cmd[0], "env", 4) == 0)
		ft_env(data);
	if (ft_strncmp(cmd->arg_cmd[0], "exit", 5) == 0)
		ft_exit(cmd, data);
	if (ft_strncmp(cmd->arg_cmd[0], "export", 7) == 0)
		ft_export(data);
	if (ft_strncmp(cmd->arg_cmd[0], "pwd", 4) == 0)
		ft_pwd(data);
	if (ft_strncmp(cmd->arg_cmd[0], "unset", 6) == 0)
		ft_unset(data, cmd->arg_cmd[1]);
	return (0);
}
