/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:41 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/13 19:28:26 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	initialize_forks(t_fork **forks, int nbr_philo)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * nbr_philo);
	if (!(*forks))
		return (write_an_error("Error ! Malloc error\n"));
	i = -1;
	while (++i < nbr_philo)
	{
		(*forks)[i].fork_id = i;
		if (pthread_mutex_init(&(*forks)[i].fork, NULL) != 0)
		{
			free_forks(*forks, i);
			return (write_an_error("Error ! Mutex Init error !\n"));
		}
	}
	return (0);
}

static void	set_philo_data(int i, t_philo **philo, t_data *data, char **argv)
{
	(*philo)[i].id = i + 1;
	(*philo)[i].nbr_philo = convert_char_to_int(argv[1]);
	if (argv[5] != NULL)
		(*philo)[i].max_meal_nbr = convert_char_to_int(argv[5]);
	else
		(*philo)[i].max_meal_nbr = -1;
	(*philo)[i].current_meal_nbr = 0;
	(*philo)[i].stop_process = &data->stop_process;
	(*philo)[i].last_meal_time = 0;
	(*philo)[i].dead_or_not = 0;
	(*philo)[i].time_to_eat = convert_char_to_int(argv[3]);
	(*philo)[i].time_to_die = convert_char_to_int(argv[2]);
	(*philo)[i].time_to_sleep = convert_char_to_int(argv[4]);
	if (i == (*philo)[i].nbr_philo - 1)
		(*philo)[i].left_fork = &data->forks[0];
	else
		(*philo)[i].left_fork = &data->forks[i + 1];
	(*philo)[i].right_fork = &data->forks[i];
	(*philo)[i].eat_mutex = &data->eat_mutex;
	(*philo)[i].write_mutex = &data->write_mutex;
	(*philo)[i].stop_process_mutex = &data->stop_mutex;
}

static int	initialize_philos(t_philo **philo, t_data *data, char **argv)
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

int	initialize_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (write_an_error("Error ! Malloc error\n"));
	(*data)->forks = NULL;
	(*data)->philo = NULL;
	(*data)->stop_process = 0;
	(*data)->meals_finished = 0;
	if (pthread_mutex_init(&(*data)->stop_mutex, NULL) != 0)
	{
		free((*data));
		return (write_an_error("Error ! Mutex Init error !\n"));
	}
	if (pthread_mutex_init(&(*data)->eat_mutex, NULL) != 0)
	{
		free((*data));
		pthread_mutex_destroy(&(*data)->stop_mutex);
		return (write_an_error("Error ! Mutex Init error !\n"));
	}
	if (pthread_mutex_init(&(*data)->write_mutex, NULL) != 0)
	{
		free((*data));
		pthread_mutex_destroy(&(*data)->eat_mutex);
		pthread_mutex_destroy(&(*data)->stop_mutex);
		return (write_an_error("Error ! Mutex Init error !\n"));
	}
	return (0);
}

/* 
	Function for Initialize all struct :
	- Initialize_data : Function for Initialize the data struct (view .h)
	- Initialize_forks : Function for Initialize all forks struct (view .h)
		- We have nbr fork struct = nbr philos.
		- All fork is a mutex.
	- Initialize_philos : Function for Initialize all philo struct (view .h)
		- In a philo struct we have all data for the futur thread. 
*/

int	init_all(t_data **data, char **argv)
{
	if (initialize_data(&(*data)) == 1)
		return (1);
	if (initialize_forks(&(*data)->forks, convert_char_to_int(argv[1])) == 1)
	{
		free_forks((*data)->forks, convert_char_to_int(argv[1]));
		pthread_mutex_destroy(&(*data)->stop_mutex);
		pthread_mutex_destroy(&(*data)->eat_mutex);
		pthread_mutex_destroy(&(*data)->write_mutex);
		free(data);
		return (1);
	}
	if (initialize_philos(&(*data)->philo, *data, argv) == 1)
	{
		free_forks((*data)->forks, convert_char_to_int(argv[1]));
		pthread_mutex_destroy(&(*data)->stop_mutex);
		pthread_mutex_destroy(&(*data)->eat_mutex);
		pthread_mutex_destroy(&(*data)->write_mutex);
		free(data);
		return (1);
	}
	return (0);
}
