/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:19:49 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/30 01:48:12 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

int take_forks_2(t_data *data, t_philosophers *philo, int left_philo)
{
		if (pthread_mutex_lock(&data->philos[left_philo].fork) != 0)
			return (-1);
		get_current_time(data);
		printf("[%ld] %d has taken a fork\n", data->elapsed_time, philo->id + 1);
		if (pthread_mutex_lock(&philo->fork) != 0)
			return (-1);
		get_current_time(data);
		printf("[%ld] %d has taken a fork\n", data->elapsed_time, philo->id + 1);
	return (0);
}

int	take_forks(t_data *data, t_philosophers *philo)
{
	int	left_philo;

	if (philo->id == 0)
		left_philo = data->nb_philo - 1;
	else
		left_philo = philo->id - 1;
	if (philo->id == data->nb_philo - 1)
	{
		if (pthread_mutex_lock(&philo->fork) != 0)
			return (-1);
		get_current_time(data);
		printf("[%ld] %d has taken a fork\n", data->elapsed_time, philo->id + 1);
		if (pthread_mutex_lock(&data->philos[left_philo].fork) != 0)
			return (-1);
		get_current_time(data);
		printf("[%ld] %d has taken a fork\n", data->elapsed_time, philo->id + 1);
	}
	else
	{
		if (take_forks_2(data, philo, left_philo) == -1)
			return (-1);
	}
	return (0);
}

int	drop_the_fork(t_data *data, t_philosophers *philo)
{
	int	left_philo;

	if (philo->id == 0)
		left_philo = data->nb_philo - 1;
	else
		left_philo = philo->id - 1;
	if (pthread_mutex_unlock(&data->philos[left_philo].fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->fork) != 0)
		return (-1);
	return (0);
}