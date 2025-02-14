/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:51:53 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:35:17 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	attribute_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		write_msg(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->right_fork->fork);
		write_msg(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		write_msg(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->left_fork->fork);
		write_msg(philo, "has taken a fork\n");
	}
	return ;
}

int	try_to_eat(t_philo *philo)
{
	attribute_fork(philo);
	pthread_mutex_lock(philo->eat_mutex);
	write_msg(philo, VERT "is eating\n" RESET);
	philo->current_meal_nbr++;
	if (get_time(&philo->last_meal_time) == -1)
		return (1);
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat, philo);
	return (0);
}
