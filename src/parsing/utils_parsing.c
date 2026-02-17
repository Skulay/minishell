/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 01:43:29 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 01:58:29 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_have_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	ft_rm_quote(t_cmd *cmd)
{
	int		i;
	t_cmd	*curr;
	char	*tmp;

	curr = cmd;
	while (curr)
	{
		i = 0;
		while (curr->arg_cmd[i])
		{
			if (ft_have_quote(curr->arg_cmd[i]))
			{
				tmp = ft_strtrim(curr->arg_cmd[i], "\'\"");
				free(curr->arg_cmd[i]);
				curr->arg_cmd[i] = tmp;
			}
			i++;
		}
		curr = curr->next;
	}
}

