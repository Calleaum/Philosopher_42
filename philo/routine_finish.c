/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:10:30 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/29 16:31:11 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	kill_philo(t_philo *philo)
{
	time_t	current_time;

	current_time = datetime_now();
	if ((current_time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->general_meal_lock);
		set_dinner_end_prop(philo->table, true);
		log_status(philo, S_DEAD);
		return (true);
	}
	return (false);
}

static bool	dinner_finished_reached(t_table *table)
{
	int		i;
	bool	eat_enough;

	i = 0;
	eat_enough = true;
	if (has_dinner_finish(table))
		return (true);
	while (i < table->nbr_philo)
	{
		pthread_mutex_lock(&table->philo[i]->general_meal_lock);
		if (kill_philo(table->philo[i]) == true)
			return (true);
		if (table->time_must_eat != -1)
			if (table->philo[i]->nbr_meals_done < table->time_must_eat)
				eat_enough = false;
		pthread_mutex_unlock(&table->philo[i]->general_meal_lock);
		i++;
	}
	if (table->time_must_eat != -1 && eat_enough == true)
	{
		set_dinner_end_prop(table, true);
		return (true);
	}
	return (false);
}

void	*finish_routines_reached(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->time_must_eat == 0)
		return (NULL);
	set_dinner_end_prop(table, false);
	while (true)
	{
		if (dinner_finished_reached(table) == true)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
