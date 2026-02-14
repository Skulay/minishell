/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:57:59 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/14 18:08:52 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	is_redir_out(char c)
{
	if (c == '>')
		return (true);
	return (false);
}

bool	is_redir_in(char c)
{
	if (c == '<')
		return (true);
	return (false);
}
