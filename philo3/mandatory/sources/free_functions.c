/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:33:20 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:54:28 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for free all forks mutex and the forks malloc */

void	free_forks(t_fork *forks, int nbr_forks)
{
	int	i;

	i = -1;
	if (forks)
	{
		while (++i < nbr_forks)
		{
			if (pthread_mutex_destroy(&forks[i].fork) != 0)
				write_an_error("Error ! error in destroy a fork Mutex !\n");
		}
		free(forks);
	}
	forks = NULL;
}

void	destroy_mutex(t_data **data)
{
	if (pthread_mutex_destroy(&(*data)->eat_mutex) != 0)
		write_an_error("Error ! error in destroy Eat Mutex !\n");
	if (pthread_mutex_destroy(&(*data)->write_mutex) != 0)
		write_an_error("Error ! error in destroy Write Mutex !\n");
	if (pthread_mutex_destroy(&(*data)->stop_mutex) != 0)
		write_an_error("Error ! error in destroy Stop Mutex !\n");
	if (pthread_mutex_destroy(&(*data)->time_mutex) != 0)
		write_an_error("Error ! error in destroy time Mutex !\n");
	return ;
}

/* Function for free all malloc data */

void	free_data(t_data **data)
{
	if (*data != NULL)
	{
		if ((*data)->forks)
			free_forks((*data)->forks, (*data)->philo[0].nbr_philo);
		if ((*data)->philo)
			free((*data)->philo);
		destroy_mutex(data);
		free(*data);
	}
}
