/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:24:48 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/02 09:55:15 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_check_var(t_data *data, char *str)
{
	t_env	*tmp;
	t_env	*prev;

	if (ft_isdigit(str[0]) || str[0] == '=' || is_special(str) || str[0] == '=')
		return (1);
	tmp = data->env_copy;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, ft_strlen(str)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env_copy = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	if (check_empty(data))
		printf("minishell: unset: `': not a valid identifier\n");
	if (data->cmd->args[i])
	{
		while (data->cmd->args[i])
		{
			str = data->cmd->args[i];
			if (_check_var(data, str))
			{
				printf("minishell: unset: `%s': not a valid identifier\n", str);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
