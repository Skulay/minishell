/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:47:02 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/18 02:10:18 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_cmd(t_cmd *command, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if(pid == 0)
	{
		execve(command->arg_cmd[0], command->arg_cmd, data->my_env);
		perror("exeve :");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork :");
	return 0;
}
