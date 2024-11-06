/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:43:59 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/02 10:01:54 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_spaces(t_token *el, int flg)
{
	while (el && el->type == WHITE_SPACE)
	{
		if (flg && el->next)
			el = el->next;
		else if (!flg && el->prev)
			el = el->prev;
		else
			break ;
	}
	return (el);
}

int	is_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '#' || s[i] == '@' || s[i] == '%' || s[i] == '!'
			|| s[i] == '^' || s[i] == '&' || s[i] == '*' || s[i] == '~'
			|| s[i] == '-' || s[i] == '+' || s[i] == '.' 
			|| s[i] == ';' || s[i] == ' '
			|| s[i] == '}' || s[i] == '{' || s[i] == '?' 
			|| s[i] == '$' || s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_empty(t_data *data)
{
	t_token	*token;

	token = data->lexer->tokens;
	while (token)
	{
		if (!ft_strncmp(data->cmd->command, token->content,
				ft_strlen(data->cmd->command)))
			break ;
		token = token->next;
	}
	if (token->next)
		token = skip_spaces(token->next, 1);
	if ((token->type == S_QUOTE || token->type == D_QUOTE)
		&& (token->next->type == S_QUOTE || token->next->type == D_QUOTE))
		return (1);
	return (0);
}
