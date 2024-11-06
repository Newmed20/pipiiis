/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:51:55 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/05 20:16:02 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pfds(t_command *current, t_fds *fds)
{
	if (current->next && current->oa_files == NULL)
	{
		if (fds->pfd[0] != -1)
			close(fds->pfd[0]);
		dup2(fds->pfd[1], STDOUT_FILENO);
		if (fds->pfd[1] != -1)
			close(fds->pfd[1]);
	}
	if ((fds->prev_pfd[0] != -1 || fds->prev_pfd[1] != 1) 
		&& current->heredoc_delimiters == NULL && current->input_files == NULL)
	{
		dup2(fds->prev_pfd[0], STDIN_FILENO);
		if (fds->prev_pfd[0] != -1)
			close(fds->prev_pfd[0]);
	}
	if (fds->prev_pfd[1] != -1)
		close(fds->prev_pfd[1]);
	if (fds->pfd[0] != -1)
		close(fds->pfd[0]);
	if (fds->pfd[1] != -1)
		close(fds->pfd[1]);
	if (fds->prev_pfd[0] != -1)
		close(fds->prev_pfd[0]);
}


t_fds	*initiate_fds(void)
{
	
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(1);
	fds->prev_pfd[0] = -1;
	fds->prev_pfd[1] = -1;
	fds->pfd[0] = -1;
	fds->pfd[1] = -1;
	return (fds);
}
// void     execute_multiple(t_data *data, char **env)
// {

// 	t_fds *fds;
//     t_command   *current ;
//     int         pid;
	
// 	fds = initiate_fds();
// 	current = data->cmd;
//     while (current)
//     {
//         // printf ("command : %s\n", current->command);
//         if (current->next && pipe(fds->pfd) == -1)
//         {
//             perror("pipe");
//             exit(1);
//         }
//         if(current->heredoc_delimiters)
//             ft_heredoc(current,data->env_copy , 0);
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             exit(1);
//         }
//         if (pid == 0)
//         {
//             // printf ("command : %s\n", current->command);
//             // handle_pfds(current, fds); 
//             if (current->next)
//                 dup2(fds->pfd[1], STDOUT_FILENO);
//             if (current != data->cmd)
//                 dup2(fds->prev_pfd[0], STDIN_FILENO);

//             close(fds->prev_pfd[0]);
//             close(fds->prev_pfd[1]);
//             close(fds->pfd[0]); 
//             close(fds->pfd[1]);
//             if (current->input_files || current->oa_files)
//                 ft_redirection(current);
//             // if(ft_isbuitin(current->command))
//             // {
//             //     execute_builtins(data);
//             //     while (1);
//             //     exit(exit_status);
//             // }       
// 	        env = ft_transform_env(data->env_copy);
//             if (execve(current->full_path, current->args, env) == -1)
//             {
//                 // free(current->full_path);
//                 // free_array(envp);
//                 exit(1);
//             }
//         }
//         else
//         {
//             close(fds->prev_pfd[0]);
//             close(fds->prev_pfd[1]);
//             fds->prev_pfd[0] = fds->pfd[0];
//             fds->prev_pfd[1] = fds->pfd[1];
//             close(fds->pfd[1]);
//             close(fds->pfd[0]);
//             wait(NULL);
//         }
//         current = current->next;
//     }
//     close(fds->prev_pfd[0]);
//     close(fds->prev_pfd[1]);
// }

void execute_multiple(t_data *data, char **env)
{
    t_fds *fds;
    t_command *current;
    t_command *test;
    // int pid;    // t_data *d;

    fds = initiate_fds();
    current = data->cmd;
    test = current;
    
    // t_command *cur = data->cmd;
    // while (cur)
    // {
    //     printf("command : %s\n", cur->command);
    //     cur = cur->next;
    // }
    while (current)
    {
        // printf("current cmd : %s\n", current->command);
        
        if (current->next && pipe(fds->pfd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        if (current->heredoc_delimiters)
            ft_heredoc(current, data->env_copy, 0);
        current->pid = fork();
        if (current->pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (current->pid == 0)
        {
            handle_pfds(current, fds);
            if (current->input_files || current->oa_files)
                ft_redirection(current);
            if(ft_isbuitin(current->command))
            {
               data->cmd = current;
                // while (1);
                execute_builtins(data);
                exit(exit_status);
            }    
            env = ft_transform_env(data->env_copy);
          
            if (execve(current->full_path, current->args, env) == -1)
            {
                // Free resources before exiting
                // free(current->full_path);
                // free_array(env);
                // perror("execve");
                 exit(1);
            }
        }
        else if (current->pid > 0)
        {
            if (fds->prev_pfd[0] != -1)
		        close(fds->prev_pfd[0]);
	        if (fds->prev_pfd[1] != -1)
		        close(fds->prev_pfd[1]);
            fds->prev_pfd[0] = fds->pfd[0];
            fds->prev_pfd[1] = fds->pfd[1];
	        close(fds->pfd[1]);
	        // return;
        }
        current = current->next;
    }
    current = test;
    while (current->next)
    {
        waitpid(current->pid, &exit_status, 0);
        current = current->next;
    }
    close(fds->prev_pfd[0]);
    close(fds->prev_pfd[1]);
}
