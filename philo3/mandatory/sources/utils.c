/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:37 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:56:49 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* It is a function for write a string in the error output. */

int	write_an_error(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i] != '\0')
		write(2, &str[i], 1);
	return (1);
}

/* Is a function for convert a string in number */

int	convert_char_to_int(char *str)
{
	int						i;
	unsigned long long int	result;

	if (!str)
		return (-1);
	i = -1;
	result = 0;
	while (str[++i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
	}
	if (result > INT_MAX)
		return (-1);
	return ((int)result);
}

int	get_time(long	*time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		write_an_error("Error ! error in get time !\n");
		return (-1);
	}
	*time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	write_msg(t_philo *philo, char *str)
{
	long	current_time;

	current_time = 0;
	if (get_time(&current_time) == -1)
		return (1);
	pthread_mutex_lock(philo->stop_process_mutex);
	if (philo->dead_or_not == 0)
		printf("%ld %d %s", current_time - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->stop_process_mutex);
	return (0);
}

void	ft_usleep(long milliseconds, t_philo *philo)
{
	long	start_time;
	long	current_time;

	current_time = 0;
	start_time = 0;
	get_time(&start_time);
	get_time(&current_time);
	while (current_time < start_time + milliseconds)
	{
		pthread_mutex_lock(philo->stop_process_mutex);
		if (philo->dead_or_not == 1)
		{
			pthread_mutex_unlock(philo->stop_process_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->stop_process_mutex);
		usleep(200);
		get_time(&current_time);
	}
	return ;
}
