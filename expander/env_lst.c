/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:10:37 by abmahfou          #+#    #+#             */
/*   Updated: 2024/09/22 14:50:41 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_lst_new(t_data *data, char *var)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(ft_strtok(var, "="));
	env->value = ft_strdup(ft_strtok(NULL, "="));
	env->next = NULL;
	data->env_copy = env;
	return (data->env_copy);
}

void	env_lst_last(t_data *data, t_env *env)
{
	t_env	*tmp;

	if (!data->env_copy)
		data->env_copy = env;
	else
	{
		tmp = data->env_copy;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env;
	}
}

t_env	*env_lst_back(t_data *data, char *var)
{
	t_env	*env;
	char	*equal;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	equal = ft_strchr(var, '=');
	if (equal != NULL)
		*equal = '\0';
	env->key = ft_strdup(var);
	if (equal)
		env->value = ft_strdup(equal + 1);
	else
		env->value = ft_strdup("");
	env->next = NULL;
	env_lst_last(data, env);
	return (data->env_copy);
}

t_data	*get_env_cpy(t_data *data, char **env)
{
	int		i;
	char	*env_var;

	i = 0;
	env_var = env[i];
	while (env_var)
	{
		if (data->env_copy == NULL)
			data->env_copy = env_lst_new(data, env_var);
		else
			data->env_copy = env_lst_back(data, env_var);
		i++;
		env_var = env[i];
	}
	return (data);
}
