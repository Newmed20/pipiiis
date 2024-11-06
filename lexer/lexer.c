/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:09:31 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/31 10:17:54 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(char *content, int len, 
		enum e_type type, enum e_state state)
{
	t_token	*token;
	char	*str;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	str = ft_strndup(content, len);
	if (!str)
		return (NULL);
	token->content = str;
	token->len = len;
	token->state = state;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int	_tokenize(char *line, t_tkn_lst *tokens, int pos, enum e_state *state)
{
	if (!not_special(line[pos]))
		pos += get_word(tokens, line + pos, *state);
	else if (line[pos] == '>' || line[pos] == '<')
		pos += _redir_tokenize(tokens, line, pos, state);
	else if (line[pos] == '|')
		lst_token_add_back(&tokens, create_token(line + (pos++), 1, 
				PIPE_LINE, *state));
	else if (ft_isspace(line[pos]))
		lst_token_add_back(&tokens, create_token(line + (pos++), 1, 
				WHITE_SPACE, *state));
	else if (line[pos] == '\'')
		_quote_tokenize(tokens, line + (pos++), S_QUOTE, state);
	else if (line[pos] == '\"')
		_quote_tokenize(tokens, line + (pos++), D_QUOTE, state);
	else if (line[pos] == '$')
		pos += _env_tokenize(tokens, line + pos, ENV, *state);
	return (pos);
}

t_tkn_lst	*lexer(char *line)
{
	t_tkn_lst		*tokens;
	enum e_state	state;
	int				i;

	if (line[0] == '\0')
		return (NULL);
	i = 0;
	tokens = NULL;
	state = GENERAL;
	tokens = malloc(sizeof(t_tkn_lst));
	if (!tokens)
		return (NULL);
	tokens->tokens = NULL;
	if (!tokens)
		return (NULL);
	while (line[i])
		i = _tokenize(line, tokens, i, &state);
	return (tokens);
}
