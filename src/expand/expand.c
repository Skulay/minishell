/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:36:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 12:43:23 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_redirs(t_cmd *cmd, t_data *data)
{
	t_redir *tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type != HEREDOC || heredoc_not_quoted(tmp))
			tmp->file = expand_var_quote(tmp->file, data);
		else
			tmp->file = rm_quotes(tmp->file);
		tmp = tmp->next;
	}
}

void	expand_args(t_cmd *cmd, t_data *data)
{
	char	**new_args;
	char	**strs;
	int		i;

	if (!cmd->arg_cmd)
		return;
	new_args = NULL;
	i = 0;
	while (cmd->arg_cmd[i])
	{
		strs = expand_split(cmd->arg_cmd[i], data);
		new_args = append_all(new_args, strs);
		free_tab(strs);
		i++;
	}
	free_tab(cmd->arg_cmd);
	cmd->arg_cmd = new_args;
}

void	ft_expand(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		expand_args(cmd, data);
		expand_redirs(cmd, data);
		cmd = cmd->next;
	}
}
