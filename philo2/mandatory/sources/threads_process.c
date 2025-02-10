/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:54:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/10 16:59:58 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	symplify_variables(t_philos **p, t_data **d, void *arg)
{
	t_philo_data	*philos_data;
	
	*p = NULL;
	*d = NULL;
	philos_data = NULL;
	philos_data = (t_philo_data *)arg;
	*p = philos_data->philo;
	*d = philos_data->data;
}

int	sleeping(t_philos *philo, t_data *data)
{
	long time;

	time = get_current_time(data);
	if (time == -1)
		return (-1);
	printf("%ld %d is sleeping\n", time, philo->id);
	usleep(data->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philos *philo, t_data *data)
{
	long time;

	time = get_current_time(data);
	if (time == -1)
		return (-1);
	printf("%ld %d is thinking\n", time, philo->id);
	return (0);
}

void	*threads_process(void *arg)
{
	t_philos *philo;
	t_data	 *data;

	symplify_variables(&philo, &data, arg);
	if (get_start_time(data) == -1)
		return (NULL);
	while (data->nbr_philo_finish_meat != data->nbr_philo)
	{
		if (try_to_eat(philo, data) == -1)
			return (NULL);
		usleep(data->time_to_eat * 1000);
		if (drop_forks(philo) == -1)
			return (NULL);
		if (sleeping(philo, data) == -1)
			return (NULL);
		if (thinking(philo, data) == -1)
			return (NULL);
	}
	return (NULL);
}

// faire en sorte de recuperer tout le temps des process a tout moment avec gettimofday
