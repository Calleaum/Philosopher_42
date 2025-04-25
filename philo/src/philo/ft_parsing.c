/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:10:27 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/09 13:55:28 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	ft_check_args(char **arguments)
{
	int	i;
	int	j;

	i = 0;
	while (arguments[i])
	{
		j = 0;
		while (arguments[i][j])
		{
			if ((arguments[i][j] != '+') && (arguments[i][j] > '9'
				|| arguments[i][j] < '0'))
			{
				free_split(arguments);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_plus(char **arguments)
{
	int	i;
	int	j;

	i = 0;
	while (arguments[i])
	{
		j = 0;
		while (arguments[i][j])
		{
			if (arguments[i][j] == '+')
			{
				if (arguments[i][j + 1] > '9' || arguments[i][j + 1] < '0')
				{
					free_split(arguments);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_max(char **arg)
{
	int	i;
	int	j;
	int	found;

	i = 1;
	j = 0;
	found = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (found != 1 && ft_d(arg[i][j]))
				found = 1;
			if (found == 1 && arg[i][j] == ' ' && ft_d(arg[i][j + 1]))
				return (0);
			j++;
		}
		i++;
		if (found == 1)
			found = 0;
		else
			return (0);
	}
	return (1);
}

int	ft_parsing(t_data *data)
{
	data->args = ft_join_args(data->argv, data->argc);
	if (!data->args)
		return (0);
	data->arguments = ft_split(data->args, ' ');
	if (!data->arguments)
	{
		free(data->args);
		return (0);
	}
	free(data->args);
	if (!ft_check_args(data->arguments))
		return (0);
	if (!ft_check_plus(data->arguments))
		return (0);
	if (!ft_check_max(data->arguments))
		return (0);
	free_split(data->arguments);
	return (1);
}
