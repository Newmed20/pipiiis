/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:35:09 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/22 15:12:39 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_token *token)
{
	return (token->type == REDIR_IN || token->type == APPEND
		|| token->type == REDIR_OUT || token->type == HERE_DOC);
}

void	get_string(t_token **token, t_data *data, char **redir, char **file)
{
	char	*tmp;

	tmp = NULL;
	while (*token)
	{
		if (((*token)->type == WHITE_SPACE && (*token)->state == GENERAL)
			|| (is_redir(*token) && (*token)->state == GENERAL)
			|| ((*token)->type == PIPE_LINE && (*token)->state == GENERAL))
			break ;
		if ((*token)->type == ENV && (*token)->state != IN_SQUOTE)
			tmp = ft_expand(data, (*token));
		else if ((*token)->type != S_QUOTE && (*token)->type != D_QUOTE)
			tmp = ft_strdup((*token)->content);
		else if ((*token)->state == IN_DQUOTE || (*token)->state == IN_SQUOTE)
			tmp = ft_strdup((*token)->content);
		*redir = ft_strjoin(*file, tmp);
		if (*file)
			free(*file);
		*file = *redir;
		free_str(&tmp);
		(*token) = (*token)->next;
	}
}

t_redir	*create_redir(t_token **token, t_data *data)
{
	t_redir	*node;
	char	*file;
	char	*redir;

	file = NULL;
	redir = NULL;
	node = init_list();
	if (!node)
		return (NULL);
	node->type = (*token)->type;
	*token = skip_spaces((*token)->next, 1);
	get_string(token, data, &redir, &file);
	node->content = ft_strdup(file);
	free(file);
	node->next = NULL;
	return (node);
}

void	handle_redirections_heredoc(t_token **token, t_command *cmd, 
									t_data *data)
{
	if ((*token)->type == REDIR_IN)
		append_to_list(&cmd->input_files, create_redir(token, data));
	else if ((*token)->type == REDIR_OUT || (*token)->type == APPEND)
		append_to_list(&cmd->oa_files, create_redir(token, data));
	else if ((*token)->type == HERE_DOC)
		handle_heredoc(token, cmd, data);
}
