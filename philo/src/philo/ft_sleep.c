/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:10:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/04/25 15:08:29 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

long long	ft_period(long long past, long long present)
{
	return (present - past);
}

void	ft_sleep(long long time, t_data *data)
{
	long long	i;

	i = ft_current_time();
	while (!(data->is_dead))
	{
		if (ft_period(i, ft_current_time()) >= time)
			break ;
		usleep(500);
	}
}
