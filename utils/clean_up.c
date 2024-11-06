/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:07:14 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/21 10:08:43 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tkn(t_token **tkn)
{
	t_token	*tmp;

	if (!*tkn || !*tkn)
		return ;
	while (*tkn)
	{
		tmp = (*tkn)->next;
		free((*tkn)->content);
		free(*tkn);
		*tkn = tmp;
	}
}

void	free_tkn_lst(t_tkn_lst **lst)
{
	t_token	*tmp;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	tmp = (*lst)->tokens;
	while (tmp)
	{
		free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*lst);
}

void	free_cmd_cmd(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		tmp = (*redir)->next;
		free((*redir)->content);
		free(*redir);
		*redir = tmp;
	}
}

void	free_command(t_command **cmd)
{
	t_command	*tmp;

	if (!*cmd || !cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		free((*cmd)->command);
		free((*cmd)->full_path);
		free_split((*cmd)->args);
		free_cmd_cmd(&(*cmd)->input_files);
		free_cmd_cmd(&(*cmd)->oa_files);
		free_cmd_cmd(&(*cmd)->heredoc_delimiters);
		free_cmd_cmd(&(*cmd)->heredoc_content);
		free(*cmd);
		*cmd = tmp;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!*env || !env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}
