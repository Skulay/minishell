/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:18 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 19:51:44 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// unset with no options

int	remove_one_env(t_data *data, char *unset)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	i = 0;
	j = 0;
	len = ft_strlen(unset);
	new = malloc(sizeof(char *) * (tab_len(data->my_env) + 1));
	if (!new)
		return (1);
	while (data->my_env[i])
	{
		if (!(ft_strncmp(data->my_env[i], unset, len) == 0
			&& (data->my_env[i][len] == '='
				|| data->my_env[i][len] == '\0')))
			new[j++] = ft_strdup(data->my_env[i]);
		i++;
	}
	new[j] = NULL;
	free_tab(data->my_env);
	data->my_env = new;
	return (0);
}

int	ft_unset(t_data *data, char **args)
{
	int i = 1;

	if (!args[1])
		return (0);
	while (args[i])
	{
		remove_one_env(data, args[i]);
		i++;
	}
	return (0);
}
