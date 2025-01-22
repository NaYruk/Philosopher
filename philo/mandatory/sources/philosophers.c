/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:34:49 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/23 00:13:44 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

/* 
	Function for initialize my data struct, she contain utils variables

	- nb_philo = number of philosophers around the table.
	- number_of_meals_for_exit = number of times the philosophers must eat
								each to be able to exit the programm.
	- time_for_die = Assign the time it takes for a philosopher to die between
					 two meals.
	- time_for_eat = Assign each Philosopher's meal time.
	- time_for_sleep = Assigne each Philosopher's spleep time.
*/

int	initialize_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
	{
		write(2, "Memory Error\n", 13);
		return (-1);
	}
	pthread_mutex_init(&((*data)->mutex), NULL);
	(*data)->nb_philo = 0;
	(*data)->number_of_meals_for_exit = 0;
	(*data)->time_for_die = 0;
	(*data)->time_for_eat = 0;
	(*data)->time_for_sleep = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = NULL;
	(void)argv;
	if (argc != 6)
		return(invalid_arguments());
	if (initialize_data(&data) == -1)
		return (1);
	if (check_and_stocking_args(data, argv) == -1)
		invalid_arguments_nbr(data);
	return (0);
}

































/*pthread_mutex_t mutex;

void* routine(void *nbr)
{
	int	i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 100000000)
	{
		*(int *)nbr = *(int *)nbr + 1;
		i++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int nbr = 0;
	int	i = 0;
	int nbr_philo = atoi(argv[1]);
	pthread_t	philo[nbr_philo];
	
	(void)argc;
	printf("Number of Philosophers : %d\n", nbr_philo);
	pthread_mutex_init(&mutex, NULL);
	while (i < nbr_philo)
	{
		pthread_create(philo + i, NULL, &routine, &nbr);
		printf("Thread %d is start\n", i);
		i++;
	}
	i = 0;
	while (i < nbr_philo)
	{
		pthread_join(philo[i], NULL);
		printf("Thread %d is end\n", i);
		i++;
	}
	printf("Number after Philosophers work : %d\n", nbr);
	pthread_mutex_destroy(&mutex);
	return (0);
}*/

