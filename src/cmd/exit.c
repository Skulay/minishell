/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:57:09 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/05 17:59:46 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->arg_cmd[1])
	{
		code = data->last_exit_code;
		free_all(cmd, data);
		exit(code);
	}
	if (cmd->arg_cmd[2])
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!is_numeric(cmd->arg_cmd[1]))
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg_cmd[0], STDERR_FILENO);
		ft_putstr_fd(" : numeric argument required\n", STDERR_FILENO);
		free_all(cmd, data);
		exit(255);
	}
	code = ft_atoi(cmd->arg_cmd[1]) % 256;
	free_all(cmd, data);
	exit(code);
}
