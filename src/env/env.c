/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 05:47:09 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 07:24:02 by alehamad         ###   ########.fr       */
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
	my_envtmp = ft_calloc(5, sizeof(char *));
	path = getcwd(NULL, 0);
	my_envtmp[0] = ft_strjoin("PWD=", path);
	my_envtmp[1] = ft_strjoin("SHLVL=", "1");
	my_envtmp[2] = ft_strjoin("PATH=", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	my_envtmp[3] = ft_strjoin("_=", "./minishell");
	my_envtmp[4] = NULL;
	env->my_env = my_envtmp;
	free(path);
	return (env);
}

t_data	*copy_my_env(char **env)
{
	t_data	*data;
	char	**my_envtmp;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	my_envtmp = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		my_envtmp[i] = ft_strdup(env[i]);
		i++;
	}
	my_envtmp[i] = NULL;
	data->my_env = my_envtmp;
	return (data);
}
