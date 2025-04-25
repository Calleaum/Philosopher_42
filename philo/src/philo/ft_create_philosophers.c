/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:34 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:10:48 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->eat);
	while (i < data->philos_num)
	{
		pthread_detach(data->philosopher[i].thread_id);
		pthread_mutex_destroy(data->philosopher[i].right_fork);
		pthread_mutex_destroy(data->philosopher[i].left_fork);
		i++;
	}
}

int	ft_join_destroy(t_data *data)
{
	int	i;

	i = 0;
	if (ft_check_dead(data))
	{
		ft_destroy(data);
		free(data);
		return (0);
	}
	while (i < data->philos_num)
	{
		if (pthread_join(data->philosopher[i].thread_id, NULL) != 0)
		{
			free(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_create_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->birth = ft_current_time();
	while (i < data->philos_num)
	{
		data->philosopher[i].last_meal = ft_current_time();
		data->n = &data->philosopher[i];
		if (pthread_create(&data->n->thread_id, NULL, &routine, data->n) != 0)
		{
			free(data);
			return (0);
		}
		usleep(100);
		i++;
	}
	if (!ft_join_destroy(data))
		return (0);
	return (1);
}
