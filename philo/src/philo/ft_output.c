/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:10:13 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:08:17 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_output(t_data *data, int philo_id, char *str)
{
	pthread_mutex_lock(&data->output);
	if (!(data->is_dead))
	{
		printf("[%lld] ", ft_current_time() - data->birth);
		printf("Philosopher %d %s\n", philo_id, str);
	}
	pthread_mutex_unlock(&data->output);
}
