/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:29:39 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/10 16:57:25 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks_even(t_philos *philo, t_data *data)
{
	long	actual_time;
	
	actual_time = 0;
	if (pthread_mutex_lock(&philo->left_fork->fork) != 0)
		return (-1);
	actual_time = get_current_time(data);
	if (actual_time == -1)
		return (-1);
	printf("%ld %d has taken a fork\n", actual_time, philo->id);
	if (pthread_mutex_lock(&philo->right_fork->fork) != 0)
		return (-1);
	actual_time = get_current_time(data);
	if (actual_time == -1)
		return (-1);
	printf("%ld %d has taken a fork\n", actual_time, philo->id);
	return (0);
}

int	take_forks_odd(t_philos *philo, t_data *data)
{
	long	actual_time;
	
	actual_time = 0;
	if (pthread_mutex_lock(&philo->right_fork->fork) != 0)
		return (-1);
	actual_time = get_current_time(data);
	if (actual_time == -1)
		return (-1);
	printf("%ld %d has taken a fork\n", actual_time, philo->id);
	if (pthread_mutex_lock(&philo->left_fork->fork) != 0)
		return (-1);
	actual_time = get_current_time(data);
	if (actual_time == -1)
		return (-1);
	printf("%ld %d has taken a fork\n", actual_time, philo->id);
	return (0);
}

int	take_forks(t_philos *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		if (take_forks_even(philo, data) == -1)
			return (-1);
	}
	else
	{
		if (take_forks_odd(philo, data) == -1)
			return (-1);
	}
	return (0);
}

int	drop_forks(t_philos *philo)
{
	if (pthread_mutex_unlock(&philo->right_fork->fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->left_fork->fork) != 0)
		return (-1);
	return (0);
}