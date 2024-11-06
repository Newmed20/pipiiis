/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 03:08:36 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/02 09:12:58 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char **args, int *flag)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-n", 2))
		{
			j = 2;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
			*flag = 0;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_command *command)
{
	int		i;
	int		flag;
	char	**args;

	args = command->args;
	flag = 1;
	i = is_option(args, &flag);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!args[1] || flag)
		ft_putstr_fd("\n", 1);
	exit_status = 0;
	return (0);
}
