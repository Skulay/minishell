/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:59:58 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/21 12:47:33 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// export affiche toute les var meme sans valeur en ordre ASCII
// recrer un nouveau tableau de var et les trier print ce tableau sans toucher a env

void	ft_print_export(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		printf("export %s\n", export[i]);
		i++;
	}
}

void	ft_sort_char_tab(char **export)
{
	int		i;
	int		swp;
	char	*tmp;

	if (!export)
		return ;
	swp = 1;
	while (swp)
	{
		swp = 0;
		i = 0;
		while (export[i] && export[i + 1])
		{
			if (strcmp(export[i], export[i + 1]) > 0)
			{
				tmp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = tmp;
				swp = 1;
			}
			i++;
		}
	}
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

void	ft_export(t_data *data)
{
	int		i;
	char	**export;

	i = 0;
	export = malloc(sizeof(char *) * tab_len(data->my_env) + 1);
	if (!export)
		return ;
	while (data->my_env[i])
	{
		export[i] = malloc(sizeof(char) * strlen(data->my_env[i]) + 1);
		if (!export[i])
		{
			free_tab(export);
			return ;
		}
		ft_strcpy(export[i], data->my_env[i]);
		i++;
	}
	export[i] = '\0';
	ft_sort_char_tab(export);
	ft_print_export(export);
	free_tab(export);
}
