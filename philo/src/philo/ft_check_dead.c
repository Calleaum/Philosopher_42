/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:50:26 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:07:40 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	ft_check_total_eat(t_data *data)
{
	if (data->argc == 6 && data->total >= data->philos_num * data->must_eat)
		return (1);
	return (0);
}

int	ft_check_dead(t_data *data)
{
	int			i;

	while (1)
	{
		i = 1;
		while (i <= data->philos_num)
		{
			if (ft_check_total_eat(data))
				return (1);
			data->time = ft_current_time();
			data->norm = data->philosopher[i - 1].last_meal;
			if ((data->time - data->norm) >= data->time_to_die)
			{
				data->is_dead = 1;
				pthread_mutex_lock(&data->output);
				data->norm2 = data->time - data->birth;
				printf("[%lld] Philosopher %d died \n", data->norm2, i);
				return (1);
			}
		}
	}
	return (0);
}
