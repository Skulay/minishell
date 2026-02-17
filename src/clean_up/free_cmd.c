/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 06:40:50 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 07:38:05 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*next;
	int		i;

	curr = cmd;
	while (curr)
	{
		next = curr->next;
		if (curr->redir)
			free_redir(curr->redir);
		if (curr->arg_cmd)
		{
			i = 0;
			while (curr->arg_cmd[i])
			{
				free(curr->arg_cmd[i]);
				i++;
			}
			free(curr->arg_cmd);
		}
		free(curr);
		curr = next;
	}
}
