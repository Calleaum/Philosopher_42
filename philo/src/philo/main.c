/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:16 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:05:45 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	ft_init_data(t_data *data)
{
	data->philos_num = ft_atoi(data->argv[1]);
	data->time_to_die = ft_atoi(data->argv[2]);
	data->time_to_eat = ft_atoi(data->argv[3]);
	data->time_to_sleep = ft_atoi(data->argv[4]);
	if (data->argv[5])
		data->must_eat = ft_atoi(data->argv[5]);
	else
		data->must_eat = -1;
	data->is_dead = 0;
	data->all_ate = 0;
	if (data->philos_num < 1)
		return (0);
	return (1);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		data->philosopher[i].eat = 0;
		data->philosopher[i].philo_id = i + 1;
		data->philosopher[i].data = data;
		data->philosopher[i].right_fork = &data->fork[i];
		if (i == (data->philos_num - 1))
			data->philosopher[i].left_fork = &data->fork[0];
		else
			data->philosopher[i].left_fork = &data->fork[i + 1];
		i++;
	}
}

int	ft_start_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			free(data);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->output, NULL) != 0)
	{
		free(data);
		return (0);
	}
	if (pthread_mutex_init(&data->eat, NULL) != 0)
	{
		free(data);
		return (0);
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (ac != 5 && ac != 6)
		return (1);
	data->argc = ac;
	data->argv = av;
	if (!ft_parsing(data))
		return (1);
	if (!ft_init_data(data))
		return (1);
	if (!ft_start_mutex(data))
		return (1);
	ft_init_philo(data);
	if (!ft_create_philosophers(data))
		return (1);
	return (0);
}
