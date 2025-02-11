/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:46:32 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/11 09:56:50 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_nbr_arg(void)
{
	write(2, "Number of Arguments is invalid\n", 31);
	write(2, "Need 6 Arguments : \n", 20);
	write(2, "./exec nb_philosophers time_to_die time_to_eat ", 47);
	write(2, "time_to_sleep nb_meals_for_exit\n", 32);
	return (-1);
}

int	error_args(void)
{
	write(2, "One or more arguments are invalid\n", 34);
	write(2, "Numbers need to be < INT_MAX and >= 0\n", 38);
	return (-1);
}

int	memory_error(void)
{
	write(2, "Error in a malloc\n", 18);
	return (-1);
}

int	thread_error(void)
{
	write(2, "Error in a Thread\n", 18);
	return (-1);
}
int	mutex_error(t_data *data, int nbr_mutex_destroy)
{
	int	i;

	i = -1;
	write(2, "Error in a Mutex\n", 17);
	if (i + 1 < nbr_mutex_destroy)
		pthread_mutex_destroy(&data->data_mutex);
	while (++i < nbr_mutex_destroy)
		pthread_mutex_destroy(&data->forks[i].fork);
	free(data->forks);
	free(data);
	return (-1);
}