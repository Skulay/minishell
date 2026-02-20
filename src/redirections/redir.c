/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:52:33 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/20 03:30:47 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
static int	ft_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static int	ft_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirection_manager(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			ft_redir_out(redir);
		else if (redir->type == APPEND)
			ft_append(redir);
		else if (redir->type == REDIR_IN)
			ft_redir_in(redir);
		redir = redir->next;
	}
	return (0);
}
