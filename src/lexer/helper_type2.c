/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_type2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:29:12 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/14 18:52:08 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_word(char c)
{
	if (!is_space(c) && !is_operator(c))
		return (true);
	return (false);
}

bool	is_append(char c, char d)
{
	if (c == '>' && d == '>')
		return (true);
	return (false);
}

bool	is_heredoc(char c, char d)
{
	if (c == '<' && d == '<')
		return (true);
	return (false);
}

bool	is_error_syntax(char c, char d)
{
	if (c == '&')
		return (true);
	if (c == '|' && d == '|')
		return (true);
	return (false);
}
