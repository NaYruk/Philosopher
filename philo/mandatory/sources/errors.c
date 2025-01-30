/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:45:53 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/29 19:28:06 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

/* Function for free all memory malloc */

void	free_all(t_data *data, int destroy_fork)
{
	int	i;

	i = -1;
	if (data != NULL)
	{
		pthread_mutex_destroy(&(data->mutex));
		if (destroy_fork == 1)
		{
			while (++i != data->nb_philo)
				pthread_mutex_destroy(&data->philos[i].fork);
		}
		free(data->philos);
		free(data);
	}
	return ;
}

/* Function execute if argument is != 6 */

int	invalid_arguments(void)
{
	write(2, "Number of Arguments is invalid\n", 31);
	write(2, "Need 6 Arguments : \n", 20);
	write(2, "./exec nb_philosophers time_to_die time_to_eat ", 47);
	write(2, "time_to_sleep nb_dish_for_exit\n", 32);
	return (1);
}

/* Function execute if invalid nbr in args is detected */

int	invalid_arguments_nbr(t_data *data)
{
	free_all(data, 0);
	write(2, "A Number is Invalid\n", 20);
	write(2, "Need a positive number !\n", 26);
	return (1);
}

int	creating_thread_error(t_data *data)
{
	free_all(data, 1);
	write(2, "Error in thread creation !\n", 27);
	return (-1);
}

void	*error_in_a_thread(t_thread_data *thread_data)
{
	free_all(thread_data->data, 1);
	free(thread_data);
	write(2, "Error in a thread\n", 18);
	return (NULL);
}

void	*error_with_a_fork(t_thread_data *thread_data)
{
	free_all(thread_data->data, 1);
	free(thread_data);
	write(2, "Error, with a fork\n", 19);
	return (NULL);
}