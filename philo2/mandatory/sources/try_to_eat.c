/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:48:28 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/10 16:57:34 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	try_to_eat(t_philos *philo, t_data *data)
{
	(void)data;
	if (take_forks(philo, data) == -1)
		return (-1);
	philo->time_last_meal = get_current_time(data);
	if (philo->time_last_meal == -1)
		return (-1);
	printf("%ld %d is eating\n", philo->time_last_meal, philo->id);
	philo->counter_of_meal++;
	if (philo->counter_of_meal == data->max_meals_nbr)
		data->nbr_philo_finish_meat++;
	return (0);
}
