/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:47:02 by tkhider           #+#    #+#             */
/*   Updated: 2026/02/17 15:43:49 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exec_cmd(t_cmd *command)
{
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0)
    {
        char *environ[] = { NULL }; // var de test, en attendant d'avoir une vrai variable qui stock les vars d'environnements
        execve(command->arg_cmd[0], command->arg_cmd, environ);
        perror("exeve :");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
        waitpid(pid, &status, 0);
    else
        perror("fork :");
    return 0; 
}