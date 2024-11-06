/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:46 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/08 10:19:15 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

bool		not_special(char c);
void		lst_token_add_back(t_tkn_lst **lst, t_token *new);
int			get_word(t_tkn_lst *tokens, char *line, enum e_state state);
t_token		*create_token(char *content, int len, enum e_type type, 
				enum e_state state);
int			_redir_tokenize(t_tkn_lst *tokens, char *line, int pos, 
				enum e_state *state);
void		_quote_tokenize(t_tkn_lst *tokens, char *line, enum e_type type, 
				enum e_state *state);
char		*ft_strndup(const char *s1, int n);
int			_env_tokenize(t_tkn_lst *tokens, char *line, 
				enum e_type type, enum e_state state);
t_tkn_lst	*lexer(char *line);

#endif