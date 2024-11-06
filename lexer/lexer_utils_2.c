/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:48:18 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/10 10:45:36 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_word(t_tkn_lst *tokens, char *line, enum e_state state)
{
	int	i;

	i = 0;
	while (line[i] && !not_special(line[i]))
		i++;
	lst_token_add_back(&tokens, create_token(line, i, WORD, state));
	return (i);
}

int	_redir_tokenize(t_tkn_lst *tokens, char *line, int pos, enum e_state *state)
{
	int	i;

	i = pos;
	if (line[pos] == '>')
	{
		if (line[pos + 1] == '>')
			lst_token_add_back(&tokens, create_token(line + (pos++), 2, 
					APPEND, *state));
		else
			lst_token_add_back(&tokens, create_token(line + (pos), 1, 
					REDIR_OUT, *state));
		pos++;
	}
	else if (line[pos] == '<')
	{
		if (line[pos + 1] == '<')
			lst_token_add_back(&tokens, create_token(line + (pos++), 2, 
					HERE_DOC, *state));
		else
			lst_token_add_back(&tokens, create_token(line + (pos), 1, 
					REDIR_IN, *state));
		pos++;
	}
	return (pos - i);
}

void	_quote_tokenize(t_tkn_lst *tokens, char *line, 
		enum e_type type, enum e_state *state)
{
	enum e_type		tp;
	enum e_state	st;

	if (type == S_QUOTE)
	{
		tp = S_QUOTE;
		st = IN_SQUOTE;
	}
	else if (type == D_QUOTE)
	{
		tp = D_QUOTE;
		st = IN_DQUOTE;
	}
	if (*state == GENERAL)
	{
		lst_token_add_back(&tokens, create_token(line, 1, tp, GENERAL));
		*state = st;
	}
	else if (*state == st)
	{
		*state = GENERAL;
		lst_token_add_back(&tokens, create_token(line, 1, tp, GENERAL));
	}
	else
		lst_token_add_back(&tokens, create_token(line, 1, tp, st));
}

int	_env_tokenize(t_tkn_lst *tokens, char *line, 
	enum e_type type, enum e_state state)
{
	int	i;

	i = 1;
	if (line[i] == '?' || (line[i] >= '0' && line[i] <= '9'))
		i++;
	else
		while (ft_isalnum(line[i]) || line[i] == '_')
			i++;
	lst_token_add_back(&tokens, create_token(line, i, type, state));
	return (i);
}
