/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 01:08:05 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/02 10:51:18 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	if_exist(t_data *data, char *key, char *value)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_var(t_data *data, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	if (ft_isdigit(key[0]) || key[0] == '=' || is_special(key) || str[0] == '=')
		return (free(key), 1);
	if (str[i] == '=')
		value = ft_strdup(str + i + 1);
	else
		value = NULL;
	if (if_exist(data, key, value))
	{
		free(key);
		free(value);
		return (0);
	}
	add_env(&data->env_copy, key, value);
	free(key);
	free(value);
	return (0);
}

void	export_print(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_copy;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

int	ft_export(t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	if (check_empty(data))
		printf("minishell: export: `': not a valid identifier\n");
	else if (!data->cmd->args[i])
		export_print(data);
	else
	{
		while (data->cmd->args[i])
		{
			str = data->cmd->args[i];
			if (check_var(data, str) || check_empty(data))
			{
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
