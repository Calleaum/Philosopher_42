/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:10:24 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/29 16:43:40 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	keep_sleeping(t_philo *philo)
{
	if (has_dinner_finish(philo->table))
		return ;
	log_status(philo, S_SLEEPING);
	thread_sleep(philo->table, philo->table->time_to_sleep);
}

static bool	try_lock_forks(t_philo *phi)
{
	pthread_mutex_lock(&phi->table->fork_lock[phi->fork[F_LEFT]]);
	if (has_dinner_finish(phi->table))
	{
		pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_LEFT]]);
		return (false);
	}
	log_status(phi, S_LEFT_FORK);
	pthread_mutex_lock(&phi->table->fork_lock[phi->fork[F_RIGHT]]);
	if (has_dinner_finish(phi->table))
	{
		pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_RIGHT]]);
		pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_LEFT]]);
		return (false);
	}
	log_status(phi, S_RIGHT_FORK);
	return (true);
}

static void	keep_eating(t_philo *phi)
{
	if (has_dinner_finish(phi->table))
		return ;
	if (!try_lock_forks(phi))
		return ;
	set_last_meal_prop(phi, datetime_now());
	if (has_dinner_finish(phi->table))
	{
		pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_RIGHT]]);
		pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_LEFT]]);
		return ;
	}
	log_status(phi, S_EATING);
	thread_sleep(phi->table, phi->table->time_to_eat);
	if (!has_dinner_finish(phi->table))
		increment_times_eat_prop(phi);
	pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_RIGHT]]);
	pthread_mutex_unlock(&phi->table->fork_lock[phi->fork[F_LEFT]]);
}

static void	keep_thinking(t_philo *philo, bool log)
{
	time_t	time_thinking;

	if (has_dinner_finish(philo->table))
		return ;
	time_thinking = handle_thinking_time(philo);
	if (log == true && !has_dinner_finish(philo->table))
		log_status(philo, S_THINKING);
	thread_sleep(philo->table, time_thinking);
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
	while (!has_dinner_finish(philo->table))
	{
		keep_eating(philo);
		if (has_dinner_finish(philo->table))
			break ;
		keep_sleeping(philo);
		if (has_dinner_finish(philo->table))
			break ;
		keep_thinking(philo, true);
	}
	return (NULL);
}
