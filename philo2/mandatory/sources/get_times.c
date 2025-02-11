/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_times.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:05 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/11 12:55:22 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_start_time(t_data *data)
{
	struct timeval	tv;
	long	start_time;
	
	pthread_mutex_lock(&data->data_mutex);
	start_time = 0;
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&data->data_mutex);
	return (start_time);
}

long	get_current_time(t_data *data)
{
	struct timeval	tv;
	long	elapsed_time;

	pthread_mutex_lock(&data->data_mutex);
	elapsed_time = 0;
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	elapsed_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&data->data_mutex);
	return (elapsed_time);
}