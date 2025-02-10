/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_times.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:05 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/10 16:55:49 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_start_time(t_data *data)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	data->start_time_in_ms = tv.tv_usec;
	data->start_time = tv.tv_sec;
	return (0);
}

long	get_current_time(t_data *data)
{
	struct timeval	tv;
	long			elapsed_time;
	long			elasped_usec;
	long			elasped_time_in_ms;

	elapsed_time = 0;
	elasped_usec = 0;
	elasped_time_in_ms = 0;
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	elapsed_time = tv.tv_sec - data->start_time;
	elasped_usec = tv.tv_usec - data->start_time_in_ms;
	elasped_time_in_ms = elapsed_time * 1000 + elasped_usec / 1000;
	return (elasped_time_in_ms);
}