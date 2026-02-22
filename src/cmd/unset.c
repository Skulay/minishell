/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:18 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 11:07:18 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// unset with no options

int	ft_unset(t_data *data, char *unset)
{
	int		i;
	int		j;
	char	**new;
	int		unset_len;

	i = 0;
	j = 0;
	unset_len = ft_strlen(unset);
	new = malloc(sizeof(char *) * tab_len(data->my_env) + 1);
	if (!new)
		return (1);
	while (data->my_env[i])
	{
		if (!(ft_strncmp(data->my_env[i], unset, unset_len) == 0
			&& data->my_env[i][unset_len] == '='))
		{
			new[j] = ft_strdup(data->my_env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_tab(data->my_env);
	data->my_env = new;
	return (0);
}
