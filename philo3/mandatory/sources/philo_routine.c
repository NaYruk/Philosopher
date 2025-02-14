/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:27 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:59:29 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	if (write_msg(philo, "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo->time_to_sleep, philo);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (write_msg(philo, "is thinking\n") == 1)
		return (1);
	return (0);
}

static int	philo_alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (write_msg(philo, "has taken a fork\n") == 1)
		return (1);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->time_mutex);
	if (get_time(&philo->start_time) == -1)
		return (NULL);
	pthread_mutex_unlock(philo->time_mutex);
	if (philo->nbr_philo == 1)
		return (philo_alone(philo), NULL);
	pthread_mutex_lock(philo->stop_process_mutex);
	while (philo->dead_or_not == 0)
	{
		pthread_mutex_unlock(philo->stop_process_mutex);
		if (try_to_eat(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
		pthread_mutex_lock(philo->stop_process_mutex);
	}
	pthread_mutex_unlock(philo->stop_process_mutex);
	return (NULL);
}
