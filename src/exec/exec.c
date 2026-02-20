/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:47:02 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/19 23:16:50 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_cmd(t_cmd *command, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*valid_path;

	if (!command || !command->arg_cmd || !command->arg_cmd[0])
		return (0);
	valid_path = findvalidpath(data->my_env, command->arg_cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		if (redirection_manager(command->redir) != 0)
			exit(1);
		if (!valid_path)
		{
			ft_putstr_fd("Command not found \n", 2);
			exit(127);
		}
		execve(valid_path, command->arg_cmd, data->my_env);
		perror("exeve");
		exit(126);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
	free(valid_path);
	return (0);
}
