/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:08:11 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_eat(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	ft_output(philosopher->data, philosopher->philo_id, "🍴 has taken a fork");
	pthread_mutex_lock(philosopher->left_fork);
	ft_output(philosopher->data, philosopher->philo_id, "🍴 has taken a fork");
	ft_output(philosopher->data, philosopher->philo_id, "🍕 is eating");
	philosopher->last_meal = ft_current_time();
	ft_sleep(philosopher->data->time_to_eat, philosopher->data);
	philosopher->data->total++;
	pthread_mutex_lock(&philosopher->data->eat);
	philosopher->eat++;
	pthread_mutex_unlock(&philosopher->data->eat);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}
