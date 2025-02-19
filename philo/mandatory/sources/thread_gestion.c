/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:15 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/19 20:23:34 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
	Function for create all threads :
	- Monitoring Thread
	- Philosophers Threads
*/

int	create_threads(t_data *data)
{
	int		i;
	long	start_time;

	i = -1;
	get_time(&start_time);
	while (++i < data->philo[0].nbr_philo)
		data->philo[i].start_time = start_time;
	i = -1;
	while (++i < data->philo[0].nbr_philo)
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, &philo_routine, &data->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (write_an_error("Error ! error in creation of threads !\n"));
		}
	}
	if (pthread_create(&data->monitoring_thread, NULL, &monitoring, data) != 0)
	{
		while (--i >= 0)
			pthread_join(data->philo[i].thread, NULL);
		return (write_an_error("Error ! error in creation of threads !\n"));
	}
	return (0);
}

/*
	Function for Waiting all threads :
	- Monitoring Thread
	- Philosophers Threads
*/

int	wait_threads(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < data->philo[0].nbr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			status = 1;
	}
	if (pthread_join(data->monitoring_thread, NULL) != 0)
		status = 1;
	if (status == 1)
		return (write_an_error("Error ! error in waiting a Thread !\n"));
	return (0);
}
