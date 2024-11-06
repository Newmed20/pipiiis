/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:42:10 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/04 17:24:41 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_lstclear_list(t_redir **head)
{
	t_redir	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current->content);
		free(current);
	}
	if (!(*head))
		free(*head);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_clear_command(t_command **cmd)
{
	t_command	*current;

	current = *cmd;
	free(current->command);
	free_array(current->args);
	ft_lstclear_list(&current->input_files);
	ft_lstclear_list(&current->oa_files);
	ft_lstclear_list(&current->heredoc_delimiters);
	if (current->full_path)
		free(current->full_path);
	*cmd = (*cmd)->next;
	free (current);
}

