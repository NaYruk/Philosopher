/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:54:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/11 15:15:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sleeping(t_philos *philo, t_data *data)
{
	long time;
	
	time = get_current_time(data);
	if (time == -1)
		return (-1);
	printf("%ld %d is sleeping\n", time - data->start_time, philo->id);
	usleep(data->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philos *philo, t_data *data)
{
	long time;

	time = get_current_time(data);
	if (time == -1)
		return (-1);
	printf("%ld %d is thinking\n", time - data->start_time, philo->id);
	return (0);
}

void	*threads_process(void *arg)
{
	t_philos *philo;
	t_data	 *data;

	philo = (t_philos *)arg;
	data = philo->data;
	while (data->nbr_philo_finish_meat != data->nbr_philo)
	{
		if (try_to_eat(philo, data) == -1)
			return (NULL);
		usleep(data->time_to_eat * 1000);
		if (drop_forks(philo) == -1)
			return (NULL);
		if (sleeping(philo, data) == -1)
			return (NULL);
		if (data->program_running == false)
			return (NULL);
		if (thinking(philo, data) == -1)
			return (NULL);
	}
	return (NULL);
}
