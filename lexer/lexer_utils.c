/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:40:39 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/30 19:41:22 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	not_special(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '$' 
		|| c == '\'' || c == '\"' || c == '\n' 
		|| c == '\0' || ft_isspace(c));
}

t_token	*get_last(t_token *last)
{
	t_token	*l;

	l = last;
	if (!l)
		return (NULL);
	while (l->next)
		l = l->next;
	return (l);
}

void	lst_token_add_back(t_tkn_lst **lst, t_token *new)
{
	t_token	*last;

	if (!*lst || !new)
		return ;
	if ((*lst)->tokens == NULL)
		(*lst)->tokens = new;
	else
	{
		last = get_last((*lst)->tokens);
		last->next = new;
		new->prev = last;
	}
}

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	str = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (*(s1 + i) && i < n)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
