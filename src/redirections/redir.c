/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:52:33 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/19 23:22:52 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redirection_manager(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
