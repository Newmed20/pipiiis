/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:19:00 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/03 15:57:02 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	dup_close(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

int	ft_output(t_redir *output_files)
{
	int	fd = -1;

	while (output_files)
	{
		if (fd != -1)
			close(fd);
		if (output_files->type == REDIR_OUT)
			fd = open(output_files->content, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			fd = open(output_files->content, O_WRONLY 
					| O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		output_files = output_files->next;
	}
	dup_close(fd);
	return (0);
}

int	ft_input(t_redir *input_file)
{
	int	fd = -1;

	while (input_file)
	{
		if (fd != -1)
			close(fd);
		fd = open(input_file->content, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		input_file = input_file->next;
	}
	dup_close(fd);
	return (0);
}

void ft_redirection(t_command *cmd)
{
	if (cmd->input_files)
		ft_input(cmd->input_files);
	if (cmd->oa_files)
		ft_output(cmd->oa_files);
}
