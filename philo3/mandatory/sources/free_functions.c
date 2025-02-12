/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:33:20 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/12 18:52:05 by mmilliot         ###   ########.fr       */
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
			pthread_mutex_destroy(&forks[i].fork);
		}
		free(forks);
	}
	forks = NULL;
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
		pthread_mutex_destroy(&(*data)->eat_mutex);
		pthread_mutex_destroy(&(*data)->write_mutex);
		free(*data);
	}
}
