/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:56:47 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/10 16:54:28 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
	Function for Initialize each Philosophers
	- Initialize all data
	- Set the right fork and left fork for each Philosophers
*/

static int	init_philosophers(t_data *data)
{
	int	i;
	data->philos = NULL;
	data->philos = malloc(sizeof(t_philos) * data->nbr_philo);
	if (!data->philos)
	{
		free_all(data);
		return (memory_error());
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_last_meal = 0;
		data->philos[i].counter_of_meal = 0;
		if (data->philos[i].id == data->nbr_philo)
			data->philos[i].left_fork = &data->forks[0];
		else
			data->philos[i].left_fork = &data->forks[data->philos[i].id];
		data->philos[i].right_fork = &data->forks[data->philos[i].id - 1];
	}
	return (0);
} 

/* 
	Function for initialize each forks : 
	if we have 5 Philosophers, we have 5 forks :
	- fork 0 = to the right of Philosopher 1.
	- fork 0 = to the left of Philosopher 5.
	- fork 1 = to the left of Philosopher 1.
	- fork 1 = to the right of Philosopher 2.
	Like a round table with a fork between each Philosophers.
*/

static int	init_forks(t_data *data)
{
	int	i;
	data->forks = malloc(sizeof(t_fork) * data->nbr_philo);
	if (!data->forks)
	{
		free(data);
		return (memory_error());
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		data->forks[i].fork_id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (mutex_error(data, i));
		i++;
	}
	return (0);
}

/* Function for convert ascii to long. */

static long	convert_in_nbr(char *str)
{
	int		i;
	long	result;

	i = -1;
	result = 0;
	while (str[++i] != '\0')
		result = (result * 10) + (str[i] - '0');
	return (result);
}

/* Function for Initialize all data */

int	init_data(char **argv, t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		return (memory_error());
	(*data)->nbr_philo = convert_in_nbr(argv[1]);
	(*data)->time_to_die = convert_in_nbr(argv[2]);
	(*data)->time_to_eat = convert_in_nbr(argv[3]);
	(*data)->time_to_sleep = convert_in_nbr(argv[4]);
	(*data)->max_meals_nbr = convert_in_nbr(argv[5]);
	(*data)->nbr_philo_finish_meat = 0;
	(*data)->start_time = 0;
	(*data)->start_time_in_ms = 0;
	if (init_forks(*data) == -1)
		return (-1);
	if (init_philosophers(*data) == -1)
		return (-1);
	return (0);
}
