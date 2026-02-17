/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:06:02 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 07:33:28 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	maj_shlvl(char **env)
{
	int		i;
	int		lvl;
	char	*new;
	char	*nbr;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			lvl = ft_atoi(env[i] + 6) + 1;
			nbr = ft_itoa(lvl);
			if (!nbr)
				return (1);
			new = ft_strjoin("SHLVL=", nbr);
			free(nbr);
			if (!new)
				return (1);
			free(env[i]);
			env[i] = new;
			return (0);
		}
		i++;
	}
	return (1);
}
