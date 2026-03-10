/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:36:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/09 23:00:59 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_redirs(t_cmd *cmd, t_data *data)
{
	t_redir	*tmp;
	char	*old_file;

	tmp = cmd->redir;
	while (tmp)
	{
		old_file = tmp->file;
		if (tmp->type != HEREDOC || heredoc_not_quoted(tmp))
			tmp->file = expand_var_quote(old_file, data);
		else
			tmp->file = rm_quotes(old_file);
		free(old_file);
		tmp = tmp->next;
	}
}

void	expand_args(t_cmd *cmd, t_data *data)
{
	char	**new_args;
	char	**strs;
	int		i;

	if (!cmd->arg_cmd)
		return ;
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
