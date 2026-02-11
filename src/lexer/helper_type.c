/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:57:59 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/11 12:32:02 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_delimiter(char c)
{
	if (c == ' ')
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

