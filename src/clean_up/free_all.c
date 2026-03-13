/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:49:33 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/13 23:15:24 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_all(t_cmd *cmd, t_data *data)
{
	if (data && data->head)
		free_cmd(data->head);
	else if (cmd)
		free_cmd(cmd);
	if (data)
		free_data(data);
	rl_clear_history();
}
