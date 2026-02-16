/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:11:01 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 03:27:22 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_redir(int type)
{
	if (type == WORD || type == PIPE)
		return (false);
	return (true);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**new_arg;

	i = 0;
	j = 0;
	while (cmd->arg_cmd && cmd->arg_cmd[i])
		i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	if (!new_arg)
		return ;
	while (j < i)
		new_arg[j] = cmd->arg_cmd[j];
	new_arg[i] = ft_strdup(arg);
	new_arg[i + 1] = NULL;
	free(cmd->arg_cmd);
	cmd->arg_cmd = new_arg;

}

void	add_redir(t_cmd *cmd, t_token *token)
{

}
