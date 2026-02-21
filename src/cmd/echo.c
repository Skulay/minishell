/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:59:38 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/21 14:27:49 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_n_option(char *arg)
{
	int i;

	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 1;
	while (cmd->arg_cmd[i] && ft_n(cmd->arg_cmd[i]))
	{
		nflag = 0;
		i++;
	}
	while (cmd->arg_cmd[i])
	{
		printf("%s", cmd->arg_cmd[i]);
		if (cmd->arg_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (nflag)
		printf("\n");
	return (0);
}
