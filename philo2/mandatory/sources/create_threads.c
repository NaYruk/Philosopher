/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:59:20 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/06 17:51:10 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_data	*data;
	
	data = (t_data *)arg;
	printf("Je suis le philosophe numero : %d\n", data->current_philo->id);
	return (NULL);
}

int	threads_create(t_data *data)
{
	t_philo_data *philo_data = NULL;
	int	i;

	i = -1;
	philo_data = malloc(sizeof(philo_data) * data->nbr_philo);
	if (!philo_data)
	{
		free_all(data);
		return (thread_error());
	}
	while (++i < data->nbr_philo)
	{
		philo_data[i].philo = &(data->philos[i]);
		philo_data[i].data = data;
		if (pthread_create(&philo_data[i].philo->thread_id, NULL, &routine, &philo_data[i]) == -1)
		{
			free_all(data);
			return (thread_error());
		}
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) == -1)
		{
			free_all(data);
			return (thread_error());
		}
	}
	return (0);
}
