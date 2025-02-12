/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:19:19 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/12 12:09:13 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	long	current_time;
	int		i;

	i = -1;
	current_time = 0;
	data = (t_data *)arg;
	i = -1;
	while (1)
	{
		while (++i != data->nbr_philo)
		{
			current_time = get_current_time(data);
			if (current_time - data->philos[i].time_last_meal > data->time_to_die && data->philos[i].time_last_meal > 0)
			{
				pthread_mutex_lock(&data->data_mutex);
				data->program_running = false;
				pthread_mutex_unlock(&data->data_mutex);
				printf("%ld %d died\n", current_time - data->start_time, data->philos[i].id);
				return (NULL);
			}
		}
		i = -1;
		usleep(1000);
	}
	return (NULL);
}
