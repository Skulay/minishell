/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 00:45:11 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/24 01:24:41 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	wait_children(pid_t last_pid, t_data *data)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_code = 128 + WTERMSIG(status);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

static void	child_manager(t_cmd *cmd, t_data *data, int prev_fd, int *fd)
{
	char	*path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (redirection_manager(cmd->redir) != 0)
		exit(1);
	if (is_builtin(cmd->arg_cmd[0]))
		exit(exec_builtin(cmd, data));
	path = findvalidpath(data->my_env, cmd->arg_cmd[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->arg_cmd, data->my_env);
	perror("fork");
	exit(126);
}

void	execute_pipeline(t_cmd *cmd, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			execution_signals_management();
			child_manager(cmd, data, prev_fd, fd);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			prev_fd = fd[0];
			close(fd[1]);
		}
		cmd = cmd->next;
	}
	wait_children(pid, data);
}
