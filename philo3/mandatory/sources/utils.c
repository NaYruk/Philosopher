/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:37 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/13 20:16:26 by mmilliot         ###   ########.fr       */
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
	int	i;
	int	result;

	if (!str)
		return (1);
	i = -1;
	result = 0;
	while (str[++i] != '\0')
		result = result * 10 + (str[i] - '0');
	return (result);
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
	pthread_mutex_lock(philo->write_mutex);
	if (get_time(&philo->current_time) == -1)
		return (1);
	if (philo->dead_or_not == 0)
		printf("%ld %d %s", philo->current_time - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->write_mutex);
	return (0);
}
