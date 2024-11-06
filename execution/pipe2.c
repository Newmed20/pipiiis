// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipe2.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/04 11:01:59 by mjadid            #+#    #+#             */
// /*   Updated: 2024/11/05 19:47:12 by mjadid           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"



// void	close_remaining_pipes(t_pipeline *pipeline)
// {
// 	if (pipeline->pfds->prev_pfd[0] != -1)
// 		close(pipeline->pfds->prev_pfd[0]);
// 	if (pipeline->pfds->prev_pfd[1] != -1)
// 		close(pipeline->pfds->prev_pfd[1]);
// 	if (pipeline->pfds->pfd[0] != -1)
// 		close(pipeline->pfds->pfd[0]);
// 	if (pipeline->pfds->pfd[1] != -1)
// 		close(pipeline->pfds->pfd[1]);
// 	close(pipeline->original_stdin);
// 	free(pipeline->pfds);
// }

// void	handle_signal_exit_status(int signum)
// {
// 	if (signum == 3 || signum == 2)
// 	{
// 		exit_status = 128 + WTERMSIG(exit_status);
// 		if (exit_status == 129)
// 			exit_status = 1;
// 		if (exit_status == 131)
// 			ft_putstr_fd("Quit: 3\n", 2);
// 	}
// }

// void	wait_for_processes(int	*pids, int count)
// {
// 	int	i;
// 	int	signum;
// 	int	tmp;

// 	i = 0;
// 	tmp = exit_status;
// 	while ((waitpid(pids[i], &exit_status, 0) != -1) && i <= count)
// 	{
// 		if (WIFEXITED(exit_status))
// 			exit_status = WEXITSTATUS(exit_status);
// 		else if (WIFSIGNALED(exit_status))
// 		{
// 			signum = WTERMSIG(exit_status);
// 			handle_signal_exit_status(signum);
// 		}
// 		i++;
// 	}
// 	if (tmp == 1)
// 		exit_status = 1;
// }


// t_pfds	*initiate_fds(void)
// {
	
// 	t_pfds	*fds;

// 	fds = malloc(sizeof(t_fds));
// 	if (!fds)
// 		exit(1);
// 	fds->prev_pfd[0] = -1;
// 	fds->prev_pfd[1] = -1;
// 	fds->pfd[0] = -1;
// 	fds->pfd[1] = -1;
// 	return (fds);
// }

// void	create_pipe(int pfd[2])
// {
// 	if (pipe(pfd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// }


// int	handle_fork_error(pid_t pid)
// {
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	return (0);
// }

// void	print_errors(char *str, char *command)
// {
// 	ft_putstr_fd("Minishell : ", 2);
// 	ft_putstr_fd(command, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("\n", 2);
// }

// void	execute_builtin_or_bin(t_data *data , t_command *current, char **envp, t_env *env)
// {
// 	if (current->command[0] == '\0')
// 	{
// 		print_errors("Command not found", "");
// 		exit(127);
// 	}
// 	if (current->command == NULL)
// 		exit(0);
// 	if (ft_isbuitin(current->command))
// 	{
// 		execute_builtins(data);
// 		exit(exit_status);
// 	}
// 	envp = ft_transform_env(env);
// 	if (execve(current->full_path, current->args, envp) == -1)
// 	{
// 		// free(current->full_path);
// 		// free_array(envp);
// 		exit(1);
// 	}
// }

// void	handle_pfds(t_command *current, t_pfds *pfds)
// {
// 	if (current->next && current->oa_files == NULL)
// 	{
// 		if (pfds->pfd[0] != -1)
// 			close(pfds->pfd[0]);
// 		dup2(pfds->pfd[1], STDOUT_FILENO);
// 		if (pfds->pfd[1] != -1)
// 			close(pfds->pfd[1]);
// 	}
// 	if ((pfds->prev_pfd[0] != -1 || pfds->prev_pfd[1] != 1) 
// 		&& current->heredoc_delimiters == NULL && current->input_files == NULL)
// 	{
// 		dup2(pfds->prev_pfd[0], STDIN_FILENO);
// 		if (pfds->prev_pfd[0] != -1)
// 			close(pfds->prev_pfd[0]);
// 	}
// 	if (pfds->prev_pfd[1] != -1)
// 		close(pfds->prev_pfd[1]);
// 	if (pfds->pfd[0] != -1)
// 		close(pfds->pfd[0]);
// 	if (pfds->pfd[1] != -1)
// 		close(pfds->pfd[1]);
// 	if (pfds->prev_pfd[0] != -1)
// 		close(pfds->prev_pfd[0]);
// }

// int	execute_parent_process(t_pfds	*pfds)
// {
// 	if (pfds->prev_pfd[0] != -1)
// 		close(pfds->prev_pfd[0]);
// 	if (pfds->prev_pfd[1] != -1)
// 		close(pfds->prev_pfd[1]);
// 	pfds->prev_pfd[0] = pfds->pfd[0];
// 	pfds->prev_pfd[1] = pfds->pfd[1];
// 	close(pfds->pfd[1]);
// 	return (0);
// }

// void	execute_child_process(t_data *data ,t_command *current, t_pfds *pfds, char **envp, t_env *env)
// {
// 	handle_pfds(current, pfds);
// 	if (current->input_files || current->oa_files)
// 		ft_redirection(current);
// 	execute_builtin_or_bin(data , current, envp, env);
// }

// void	handle_child_process(t_data *data ,t_command *current, t_pfds *pfds, char **envp, t_env *env)
// {
// 	// signal (SIGINT, sighandle);
// 	// signal(SIGQUIT, SIG_DFL);
// 	execute_child_process(data , current, pfds, envp, env);
// }

// int	execute_command_pipe(t_data *data , t_pipeline *pipeline, char **envp, t_env *env)
// {
//     // printf("im heeeeeeeeeere\n");
// 	if (pipeline->current->next)
// 		create_pipe(pipeline->pfds->pfd);
// 	ft_heredoc(pipeline->current, env, 1);
// 	if (exit_status != 24)
// 	{
// 		pipeline->pids[pipeline->i] = fork();
// 		if (handle_fork_error(pipeline->pids[pipeline->i]) == 1)
// 			return (1);
// 		if (pipeline->pids[pipeline->i] == 0)
// 			handle_child_process(data , pipeline->current, pipeline->pfds, envp, env);
// 		else
// 			execute_parent_process(pipeline->pfds);
// 		dup2(pipeline->original_stdin, STDIN_FILENO);
// 		ft_clear_command(&(pipeline->current));
// 	}
// 	else
// 	{
// 		dup2(pipeline->original_stdin, STDIN_FILENO);
// 		close(pipeline->original_stdin);
// 		while (pipeline->current)
// 			ft_clear_command(&(pipeline->current));
// 		pipeline->current = NULL;
// 	}
// 	return (0);
// }
// int	ft_lstcmdsize(t_command *lst)
// {
// 	int	count;

// 	count = 0;
// 	while (lst)
// 	{
// 		count++;
// 		lst = lst->next;
// 	}
// 	return (count);
// }

// void	initalize_pipeline(t_pipeline *pipeline, t_command *cmd)
// {
// 	int	pipe_count;

// 	pipe_count = ft_lstcmdsize(cmd);
// 	pipeline->i = 0;
// 	pipeline->current = cmd;
// 	pipeline->pids = malloc(sizeof(int) * (pipe_count + 1));
// 	pipeline->pids[pipe_count] = 0;
// 	while (pipeline->i < pipe_count)
// 	{
// 		pipeline->pids[pipeline->i] = -1;
// 		pipeline->i++;
// 	}
// 	pipeline->i = 0;
// }


// void     execute_multiple(t_data *data, char **envp)
// {
// 	t_pipeline	pipeline;

	

// 	initalize_pipeline(&pipeline, data->cmd);
// 	pipeline.original_stdin = dup(STDIN_FILENO);
// 	pipeline.pfds = initiate_fds();
// 	while (pipeline.current)
// 	{
// 		if (pipeline.i == 1024)
// 			pipeline.i = 0;
// 		if (execute_command_pipe(data ,&pipeline, envp, data->env_copy) == 1 
// 			|| exit_status == 24)
// 		{
// 			exit_status = 1;
// 			break ;  
// 		}
// 		pipeline.i++;
// 		pipeline.current = pipeline.current->next;
// 	}
// 	wait_for_processes(pipeline.pids, pipeline.i);
// 	close_remaining_pipes(&pipeline);
// 	while (pipeline.current)
// 		ft_clear_command(&(pipeline.current));
// }