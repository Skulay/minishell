/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 05:47:09 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/23 13:03:48 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*make_my_env(char **env)
{
	t_data	*data;

	if (env && env[0])
	{
		data = copy_my_env(env);
		if (data)
			maj_shlvl(data->my_env);
	}
	else
		data = craft_my_env();
	return (data);
}

t_data	*craft_my_env(void)
{
	t_data	*env;
	char	*path;
	char	**my_envtmp;

	env = malloc(sizeof(t_data));
	if (!env)
		return (NULL);
	my_envtmp = ft_calloc(3, sizeof(char *));
	path = getcwd(NULL, 0);
	my_envtmp[0] = ft_strjoin("PWD=", path);
	my_envtmp[1] = ft_strjoin("SHLVL=", "1");
	my_envtmp[2] = NULL;
	env->my_env = my_envtmp;
	free(path);
	return (env);
}

t_data	*copy_my_env(char **env)
{
	t_data	*data;
	char	**my_envtmp;
	int		i;
	int		j;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	my_envtmp = ft_calloc(tab_len(env) + 1, sizeof(char *));
	if (!my_envtmp)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			my_envtmp[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	my_envtmp[j] = NULL;
	data->my_env = my_envtmp;
	return (data);
}
