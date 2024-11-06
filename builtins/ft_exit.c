/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:46:30 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/02 10:00:21 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_xt(t_data *data)
{
	free_env(&data->env_copy);
	free_tkn_lst(&data->lexer);
	free(data->prompt);
	printf("exit\n");
	exit(exit_status);
	return (EXIT_SUCCESS);
}

int	chck_var(t_data *data, char *arg)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	while (arg[i])
	{
		if (arg[i] == '+' || arg[i] == '-')
			digits++;
		i++;
	}
	if (digits > 1)
		return (1);
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && (arg[i] != '+' && arg[i] != '-'))
			return (1);
		i++;
	}
	if (data->cmd->arg_count > 2)
		return (2);
	return (0);
}

int	ft_exit(t_data *data)
{
	int		i;
	char	*arg;

	i = 1;
	if (check_empty(data))
		printf("minishell: exit: : numeric argument required\n");
	if (!data->cmd->args[i])
		return (ft_xt(data));
	else
	{
		while (data->cmd->args[i])
		{
			arg = data->cmd->args[i];
			if (chck_var(data, arg) == 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", arg);
				return (ft_xt(data));
			}
			else if (chck_var(data, arg) == 2)
				return (printf("minishell: exit: too many arguments\n"), 0);
			i++;
		}
	}
	return (ft_xt(data));
}
