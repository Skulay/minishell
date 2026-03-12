/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 00:45:11 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/12 16:59:54 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exit_perror(char *path, t_cmd *cmd, t_data *data)
{
	int	error_code;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->arg_cmd[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (errno == EACCES)
		error_code = 126;
	else if (errno == ENOENT)
		error_code = 127;
	else
		error_code = 1;
	if (path)
		free(path);
	free_all(cmd, data);
	exit(error_code);
}

static void	wait_children(pid_t last_pid, t_data *data)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		data->last_exit_code = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
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
	{
		free_all(cmd, data);
		exit(1);
	}
	if (is_builtin(cmd->arg_cmd[0]))
		(free_all(cmd, data), exit(exec_builtin(cmd, data)));
	path = findvalidpath(data->my_env, cmd->arg_cmd[0]);
	if (!path)
		command_not_found(cmd, data, fd);
	execve(path, cmd->arg_cmd, data->my_env);
	exit_perror(path, cmd, data);
}

static void	call_child_with_sig(t_cmd *cmd, t_data *data, int prev_fd, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_manager(cmd, data, prev_fd, fd);
}

void	execute_pipeline(t_cmd *cmd, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	execution_signals_management();
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			call_child_with_sig(cmd, data, prev_fd, fd);
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
