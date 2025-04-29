/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:10:24 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/29 13:39:25 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	keep_sleeping(t_philo *philo)
{
	log_status(philo, S_SLEEPING);
	thread_sleep(philo->table, philo->table->time_to_sleep);
}

static void	keep_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
	log_status(philo, S_LEFT_FORK);
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	log_status(philo, S_RIGHT_FORK);
	log_status(philo, S_EATING);
	set_last_meal_prop(philo, datetime_now());
	thread_sleep(philo->table, philo->table->time_to_eat);
	if (has_dinner_finish(philo->table) == false)
		increment_times_eat_prop(philo);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
}

static void	keep_thinking(t_philo *philo, bool log)
{
	time_t	time_thinking;

	time_thinking = handle_thinking_time(philo);
	if (log == true)
		log_status(philo, S_THINKING);
	thread_sleep(philo->table, time_thinking);
}

static void	*lonely_philo(t_philo *philo)
{
	log_status(philo, S_LEFT_FORK);
	thread_sleep(philo->table, philo->table->time_to_die);
	log_status(philo, S_DEAD);
	return (NULL);
}

void	*dining_routines(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->time_must_eat == 0)
		return (NULL);
	set_last_meal_prop(philo, philo->table->start_dining);
	if (philo->table->nbr_philo == 1)
		return (lonely_philo(philo));
	if (philo->id % 2 != 0)
		keep_thinking(philo, false);
	while (has_dinner_finish(philo->table) == false)
	{
		keep_eating(philo);
		keep_sleeping(philo);
		keep_thinking(philo, true);
	}
	return (NULL);
}
