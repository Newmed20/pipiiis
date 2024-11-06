/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:09:38 by abmahfou          #+#    #+#             */
/*   Updated: 2024/10/16 19:48:01 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*stock;
	char		*ptr;

	if (str != NULL)
		stock = str;
	if (stock == NULL)
		return (NULL);
	while (ft_strchr(delim, *stock))
		stock++;
	if (*stock == '\0')
	{
		stock = NULL;
		return (NULL);
	}
	ptr = stock;
	while (*stock != '\0' && !ft_strchr(delim, *stock))
		stock++;
	if (*stock != '\0')
	{
		*stock = '\0';
		stock++;
	}
	else
		stock = NULL;
	return (ptr);
}
