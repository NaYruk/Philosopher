/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:59:20 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/10 16:04:40 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for wait all threads */

int	waiting_threads(t_data *data, t_philo_data *philo_data)
{
	int	i;
	
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			free(philo_data);
			free_all(data);
			return (-1);
		}
	}
	free(philo_data);
	return (0);
}

/* 
	Function for create all threads :
	- Initialize a new structure, each stuct countain one philosopher and all data.
	- Create the a new thread for each philosopher with the thread_id.
	- Waiting finish all threads with pthread_join.
*/

int	threads_create(t_data *data)
{
	t_philo_data *philo_data;
	int	i;

	philo_data = NULL;
	philo_data = malloc(sizeof(t_philo_data) * data->nbr_philo);
	if (!philo_data)
	{
		free_all(data);
		return (thread_error());
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		philo_data[i].philo = &data->philos[i];
		philo_data[i].data = data;
		//printf("Philo nb : %d\n", philo_data[i].philo->id);
		if (pthread_create(&philo_data[i].philo->thread_id, NULL, &threads_process, &philo_data[i]) != 0)
		{
			free_all(data);
			free(philo_data);
			return (thread_error());
		}
	}
	if (waiting_threads(data, philo_data) == -1)
		return (thread_error());
	return (0);
}
