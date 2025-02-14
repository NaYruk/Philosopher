/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:54:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:59:39 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_philo_data(int i, t_philo **philo, t_data *data, char **argv)
{
	(*philo)[i].id = i + 1;
	(*philo)[i].nbr_philo = convert_char_to_int(argv[1]);
	if (argv[5] != NULL)
		(*philo)[i].max_meal_nbr = convert_char_to_int(argv[5]);
	else
		(*philo)[i].max_meal_nbr = -1;
	(*philo)[i].current_meal_nbr = 0;
	(*philo)[i].last_meal_time = 0;
	(*philo)[i].dead_or_not = 0;
	(*philo)[i].time_to_eat = convert_char_to_int(argv[3]);
	(*philo)[i].time_to_die = convert_char_to_int(argv[2]);
	(*philo)[i].time_to_sleep = convert_char_to_int(argv[4]);
	if (i == (*philo)[i].nbr_philo - 1)
		(*philo)[i].left_fork = &data->forks[0];
	else
		(*philo)[i].left_fork = &data->forks[i + 1];
	if ((*philo)[i].nbr_philo > 1)
		(*philo)[i].right_fork = &data->forks[i];
	(*philo)[i].eat_mutex = &data->eat_mutex;
	(*philo)[i].write_mutex = &data->write_mutex;
	(*philo)[i].stop_process_mutex = &data->stop_mutex;
	(*philo)[i].time_mutex = &data->time_mutex;
}

int	initialize_philos(t_philo **philo, t_data *data, char **argv)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * convert_char_to_int(argv[1]));
	if (!(*philo))
		return (write_an_error("Error ! Malloc error\n"));
	i = -1;
	while (++i < convert_char_to_int(argv[1]))
	{
		set_philo_data(i, philo, data, argv);
	}
	return (0);
}
