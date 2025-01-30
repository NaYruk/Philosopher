/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:44:00 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/30 01:48:38 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

int	try_to_eat(t_data *data, t_philosophers *philo)
{
	if (get_current_time(data) == -1)
		return (-1);
	printf("[%ld] %d is eating\n", data->elapsed_time, philo->id + 1);
	usleep(data->time_for_eat * 1000);
	philo->number_of_meals++;
	if (philo->number_of_meals == data->number_of_meals_for_exit)
			data->nbr_philos_finish_meal++;
	if (data->nbr_philos_finish_meal >= data->nb_philo - 1)
		return (1);
	if (drop_the_fork(data, philo) == -1)
			return (-1);
	if (get_current_time(data) == -1)
		return (-1);
	printf("[%ld] %d is sleeping\n", data->elapsed_time, philo->id + 1);
	usleep(data->time_for_sleep * 1000);
	return (0);
}

int	think(t_data *data, t_philosophers *philo)
{
	if (get_current_time(data) == -1)
		return (-1);
	printf("[%ld] %d is thinking\n", data->elapsed_time, philo->id + 1);
	return (0);
}

void	*do_philo_actions(void *thread_data)
{
	t_thread_data	*data_thread;
	t_philosophers	*philo;
	t_data			*data;
	int				status;

	data_thread = (t_thread_data *)thread_data;
	data = data_thread->data;
	philo = data_thread->philosophers;
	if (get_start_time(data) == -1)
		return (error_in_a_thread(thread_data));
	while (data->nbr_philos_finish_meal < data->nb_philo)
	{
		if (take_forks(data, philo) == -1)
			return (error_with_a_fork(thread_data));
		status = try_to_eat(data, philo);
		if (status == -1)
			return (error_in_a_thread(thread_data));
		else if (status == 1)
			return (NULL);
		if (think(data, philo) == -1)
			return (error_in_a_thread(thread_data));
	}
	return (NULL);
}





// il me faut un compteur au tout debut qui check tout le temps, le temps que prend le repas. Le check time commence au tout debut de la simulation. A chaques fois que le 
// philosophe mange, le compteur repart au debut au debut de son repas. Il doit manger avant que le compteur arrive a son terme. Sinon il meurt on CD.