/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:03 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/13 20:30:36 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for check if the nbr of meals is reach */

bool	all_meats_finished(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < data->philo[0].nbr_philo)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philo[i].current_meal_nbr == data->philo[0].max_meal_nbr)
		{
			data->philo[i].current_meal_nbr++;
			data->meals_finished++;
		}
		pthread_mutex_unlock(&data->eat_mutex);
	}
	if (data->meals_finished == data->philo[0].nbr_philo)
		return (true);
	return (false);
}

static void	set_philo_death_value(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo[0].nbr_philo)
	{
		data->philo[i].dead_or_not = 1;
	}
	return ;
}

/* Function for check if a Philo is dead */

bool	check_philo_death(t_data *data)
{
	int		i;
	long	actual_time;

	i = -1;
	actual_time = 0;
	while (++i < data->philo[0].nbr_philo)
	{
		get_time(&actual_time);
		if (data->philo[i].last_meal_time > 0)
		{
			if (data->philo[i].time_to_die < actual_time - data->philo[i].last_meal_time)
			{
				write_msg(&data->philo[i], ROUGE "died\n" RESET);
				set_philo_death_value(data);
				return (true);
			}
		}
		else
		{
			if (data->philo[i].time_to_die < actual_time - data->philo[i].start_time)
			{
				write_msg(&data->philo[i], ROUGE "died\n" RESET);
				set_philo_death_value(data);
				return (true);
			}
		}
	}
	return (false);	
}

/* 
	Function Monitoring :

	Check each 10 MS if a philo is dead or if the nbr of meals is reach
	if one of this case is true, the simulation need to stop.
	in this case, dead = 1 and all philo threads check this variable.

*/

void	*monitoring(void *arg)
{
	t_data	*data;
	
	data = (t_data *)arg;
	usleep(100);
	while (1)
	{
		if (check_philo_death(data) == true)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_process = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		if (all_meats_finished(data) == true)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_process = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
