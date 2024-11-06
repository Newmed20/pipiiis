/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:41:16 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/26 10:32:32 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_full_path(t_data *data)
{
	char	*full_path;
	char	**paths;
	t_env	*tmp;
	int		len;

	tmp = data->env_copy;
	full_path = NULL;
	while (tmp)
	{
		len = ft_strlen(tmp->key);
		if (ft_strncmp(tmp->key, "PATH", len) == 0)
			full_path = tmp->value;
		tmp = tmp->next;
	}
	paths = ft_split(full_path, ':');
	return (paths);
}

int	ft_is_command(t_data *data, t_command *command, char *cmd)
{
	char	**paths;
	char	*full_cmd;
	char	*tmp;
	int		i;

	i = -1;
	paths = get_full_path(data);
	if (!paths)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (free_split(paths), 1);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
		{
			command->full_path = ft_strdup(full_cmd);
			free(full_cmd);
			return (free_split(paths), 1);
		}
		free(full_cmd);
	}
	return (free_split(paths), 0);
}
