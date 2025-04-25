/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:10:34 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/09 13:53:23 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	*routine(void *ptr)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)ptr;
	while (!(philosopher->data->is_dead)
		&& (philosopher->eat != philosopher->data->must_eat))
	{
		ft_eat(philosopher);
		ft_output(philosopher->data, philosopher->philo_id, "🛌 is sleeping");
		ft_sleep(philosopher->data->time_to_sleep, philosopher->data);
		ft_output(philosopher->data, philosopher->philo_id, "🧠 is thinking");
	}
	return (NULL);
}
