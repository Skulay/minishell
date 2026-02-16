/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 04:06:54 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 04:13:42 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("      REDIR type=%d file=%s\n",
			redir->type,
			redir->file);
		redir = redir->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	cmd_index;

	cmd_index = 0;
	while (cmd)
	{
		printf("CMD [%d]\n", cmd_index++);
		i = 0;
		if (cmd->arg_cmd)
		{
			while (cmd->arg_cmd[i])
			{
				printf("   ARG[%d] = %s\n", i, cmd->arg_cmd[i]);
				i++;
			}
		}
		else
			printf("   (no args)\n");
		if (cmd->redir)
			print_redir(cmd->redir);
		else
			printf("      (no redir)\n");
		printf("--------------\n");
		cmd = cmd->next;
	}
}
