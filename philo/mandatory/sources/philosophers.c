/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:34:49 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/29 19:14:31 by mmilliot         ###   ########.fr       */
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
	(*data)->nbr_philos_finish_meal = 0;
	(*data)->time_for_die = 0;
	(*data)->time_for_eat = 0;
	(*data)->time_for_sleep = 0;
	(*data)->philos = NULL;
	(*data)->elapsed_time = 0;
	return (0);
}

int	initialize_each_philosophers(t_data *data)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = -1;
	data->philos = malloc(sizeof(t_philosophers) * data->nb_philo);
	if (!data->philos)
	{
		write(2, "Memory Error\n", 13);
		return (-1);
	}
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].number_of_meals = 0;
		data->philos[i].last_meal_time = 0;
		if (pthread_mutex_init(&data->philos[i].fork, NULL) != 0)
		{
			while (++tmp != i)
				pthread_mutex_destroy(&data->philos[tmp].fork);
			free_all(data, 0);
			return (-1);
		}
	}
	return (0);
}

int	create_philos_threads(t_data *data)
{
	t_thread_data	*thread_data;
	int	i;

	thread_data = NULL;
	thread_data = malloc(sizeof(t_thread_data) * data->nb_philo);
		if (!thread_data)
			return (creating_thread_error(data));
	i = -1;
	while (++i < data->nb_philo)
	{
		thread_data[i].data = data;
		thread_data[i].philosophers = &data->philos[i];
		if (pthread_create(&data->philos[i].thread, NULL, &do_philo_actions, &thread_data[i]) != 0)
		{
			free(thread_data);
			return (creating_thread_error(data));
		}
	}
	i = -1;
    while (++i < data->nb_philo)
	{
        pthread_join(data->philos[i].thread, NULL);
	}
	free(thread_data);
	return (0);
}

/* Principal Function of the program */

int	main(int argc, char **argv)
{
	t_data			*data;
	
	data = NULL;
	if (argc != 6)
		return(invalid_arguments());
	if (initialize_data(&data) == -1)
		return (1);
	if (check_and_stocking_args(data, argv) == -1)
		invalid_arguments_nbr(data);
	if (initialize_each_philosophers(data) == -1)
		return (1);
	if (create_philos_threads(data) == -1)
		return (1);
	free_all(data, 1);
	return (0);
}






























/*#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

struct timeval start_time, current_time;
pthread_mutex_t mutex;
long microseconds;

#define TIME_LIMIT 2000
void* routine(void *nbr)
{
    int i = 0;
    long elapsed_time;
    
    pthread_mutex_lock(&mutex);
    gettimeofday(&start_time, NULL);
    printf("Temps avant : %ld ms\n", start_time.tv_usec / 1000);
	printf("Temps en seconde actuelle depuis UNIX %ld\n", start_time.tv_sec);
    
    while (i < 100000000) {
        *(int *)nbr = *(int *)nbr + 1;
        gettimeofday(&current_time, NULL);
        elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                        (current_time.tv_usec - start_time.tv_usec) / 1000;
        
        if (elapsed_time > TIME_LIMIT) {
            printf("Temps dépassé, arrêt du thread (délai : %ld ms)\n", elapsed_time);
            break;
        }
        i++;
    }

    gettimeofday(&current_time, NULL);
	printf("Temps en seconde actuelle  fin du thread depuis UNIX %ld\n", current_time.tv_sec);
    printf("Temps après : %ld ms\n", current_time.tv_usec / 1000);
    microseconds = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                        (current_time.tv_usec - start_time.tv_usec) / 1000;
    if (microseconds < 0)
        microseconds += 1000;

    printf("Temps du processus : %ld ms\n", microseconds);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char **argv)
{
    int nbr = 0;
    int i = 0;
    int nbr_philo = atoi(argv[1]);
	(void)argc;
    pthread_t philo[nbr_philo];
    
    printf("Nombre de Philosophes : %d\n", nbr_philo);
    pthread_mutex_init(&mutex, NULL);
    
    while (i < nbr_philo)
    {
        pthread_create(&philo[i], NULL, &routine, &nbr);
        i++;
    }
    
    i = 0;
    while (i < nbr_philo)
    {
        pthread_join(philo[i], NULL);
        i++;
    }
    
    printf("Nombre après le travail des Philosophes : %d\n", nbr);
    pthread_mutex_destroy(&mutex);
    return 0;
}*/


//Pour trouver l ecouler, il faut mesurer le temps du processus au debut puis a la fin et faire la diff de la fin - le debut, mais si le resultat est neg.
//ajouter 1 000 000 soit une seconde au calcul pour trouver le reel temps ecouler.

//Chaques philosophes aura une fourchette, le 1 prendre au 2, le deux au 3, le 3 au 4 et dans le cas ou il y a que 4 philo le 4 au 1.