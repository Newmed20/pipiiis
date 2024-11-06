/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 07:59:06 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/06 00:53:30 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_file(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
}

void	ft_heredoc3(t_command *cmd, int fd, t_env *env)
{
	char	*line;

    (void)env;
	line = readline(">");
	while (line && ft_strncmp(line, cmd->heredoc_delimiters->content, 
			ft_strlen(cmd->heredoc_delimiters->content) + 1))
	{
		if (cmd->heredoc_delimiters->next == NULL && line)
			write_in_file(line, fd);
		add_history(line);
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">");
	}
	if (line)
		free(line);
}

void	ft_herdoc2(t_command *cmd, t_env *env)
{
	int		fd;
	t_redir	*tmp;

	tmp = cmd->heredoc_delimiters;
	while (cmd->heredoc_delimiters)
	{
		unlink("/tmp/heredoc.txt");
		fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_heredoc3(cmd, fd, env);
		close(fd);
		cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
	}
	cmd->heredoc_delimiters = NULL;
}

void	ft_herdoc1(t_command *cmd, t_env *env)
{
	int	pid;

	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		ft_herdoc2(cmd, env);
		exit(exit_status);
	}
	else
		waitpid(pid, &exit_status, 0);
}

void	ft_heredoc(t_command *cmd, t_env *env, int flag)
{
	int	fd;
    (void)flag;
	if (!cmd->heredoc_delimiters)
		return ;
	if (exit_status == 24)
		return ;
	ft_herdoc1(cmd, env);
	if (exit_status == 1)
		exit (1);
	fd = open("/tmp/heredoc.txt", O_RDONLY);
	if (fd != -1)
	{
		// if (cmd->full_path){
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
		// }
		close(fd);		
	}
}