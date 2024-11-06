/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:47:21 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/05 22:50:47 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status = 0;

char **ft_transform_env(t_env *env)
{
    char **env_copy;
    int i;
    t_env *tmp;

    i = 0;
    tmp = env;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    env_copy = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    tmp = env;
    while(tmp)
    {
        env_copy[i] = ft_strjoin(tmp->key, "=");
        env_copy[i] = ft_strjoin(env_copy[i], tmp->value);
        i++;
        tmp = tmp->next;
    }
    env_copy[i] = NULL;
    return (env_copy);
}



int     execute_one(t_data *data , char **env )
{
    t_command *comand;
    int pid;
    
    comand = data->cmd; 
    if(ft_isbuitin(comand->command))
    {
        execute_builtins(data);
        return (0);
    }

    pid = fork();
    if(pid == 0)
    {
        if(comand->input_files || comand->oa_files)
            ft_redirection(comand);
        if(comand->heredoc_delimiters)
            ft_heredoc(comand , data->env_copy , comand->heredoc_delimiters->state);
        if(comand->full_path)
            execve(comand->full_path, comand->args, env);
        else
            exit(EXIT_FAILURE);
    }
    
    else
    {
        waitpid(pid, &exit_status, 0);
        if (WIFEXITED(exit_status))
            exit_status = WEXITSTATUS(exit_status);
        // printf("exit status : %d\n", exit_status);
    }
    return (0);
}


int     ft_execute(t_data *data)
{
    t_command *cmd;
    char **env;

    
    env = ft_transform_env(data->env_copy);
    cmd = data->cmd;
    if(!cmd->pipe_out)
        execute_one(data , env);
    else
        execute_multiple(data , env);
    return (0);
} 