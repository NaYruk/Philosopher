/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:59:20 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/11 15:42:51 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for wait all threads */

int	waiting_threads(t_data *data, t_philos *philos)
{
	int	i;
	
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			free_all(data);
			return (-1);
		}
	}
	/* if (pthread_join(data->monitoring_id, NULL) != 0)
	{
		free_all(data);
		return (-1);
	} */
	return (0);
}

/* 
	Function for create all threads :
	- Initialize a new structure, each stuct countain one philosopher and all data.
	- Create the a new thread for each philosopher with the thread_id.
	- Waiting finish all threads with pthread_join.
*/

int	threads_create(t_data *data, t_philos *philos)
{
	int	i;

	i = -1;
	data->start_time = get_start_time(data);
	/* if (pthread_create(&data->monitoring_id, NULL, &monitoring, data) != 0)
	{
		free_all(data);
		return (thread_error());
	} */
	while (++i < data->nbr_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &threads_process, &philos[i]) != 0)
		{
			free_all(data);
			return (thread_error());
		}
	}
	if (waiting_threads(data, philos) == -1)
		return (thread_error());
	return (0);
}
