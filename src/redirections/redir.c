/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:52:33 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/03 16:55:58 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;
	size_t	len;

	len = ft_strlen(redir->file);
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);

	if (!redir->quote)
		ft_heredoc_expand(line);
	else
		ft_herodoc_not_quoted(line);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!redir->quote)
			line = ft_heredoc_expand(line);
		if (ft_strncmp(line, redir->file, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

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
	return (0);
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
		if (redir->type == REDIR_OUT && ft_redir_out(redir) != 0)
			return (1);
		else if (redir->type == APPEND && ft_append(redir) != 0)
			return (1);
		else if (redir->type == REDIR_IN && ft_redir_in(redir) != 0)
			return (1);
		else if (redir->type == HEREDOC && ft_heredoc(redir) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}
