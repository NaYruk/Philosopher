/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:56:41 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:55:13 by mmilliot         ###   ########.fr       */
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

int	initialize_mutex(t_data **data)
{
	if (pthread_mutex_init(&(*data)->time_mutex, NULL) != 0)
		return (free((*data)), write_an_error("Error ! Mutex Init error !\n"));
	if (pthread_mutex_init(&(*data)->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*data)->time_mutex);
		free((*data));
		return (write_an_error("Error ! Mutex Init error !\n"));
	}
	if (pthread_mutex_init(&(*data)->eat_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*data)->time_mutex);
		pthread_mutex_destroy(&(*data)->stop_mutex);
		free((*data));
		return (write_an_error("Error ! Mutex Init error !\n"));
	}
	if (pthread_mutex_init(&(*data)->write_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*data)->time_mutex);
		pthread_mutex_destroy(&(*data)->eat_mutex);
		pthread_mutex_destroy(&(*data)->stop_mutex);
		free((*data));
		return (write_an_error("Error ! Mutex Init error !\n"));
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
	(*data)->meals_finished = 0;
	if (initialize_mutex(data) == 1)
		return (1);
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
		destroy_mutex(data);
		free(data);
		return (1);
	}
	if (initialize_philos(&(*data)->philo, *data, argv) == 1)
	{
		free_forks((*data)->forks, convert_char_to_int(argv[1]));
		destroy_mutex(data);
		free(data);
		return (1);
	}
	return (0);
}
