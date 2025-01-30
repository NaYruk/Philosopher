/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_times.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:10 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/29 20:19:14 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

int 	get_current_time(t_data *data)
{
	int	status;
	
	status = pthread_mutex_lock(&data->mutex);
	if (status != 0)
		return (-1);
	status = gettimeofday(&data->current_time, NULL);
	if (status == -1)
		return (-1);
	data->elapsed_time = ((data->current_time.tv_sec - data->start_time.tv_sec) * 1000 +
							(data->current_time.tv_usec - data->start_time.tv_usec) / 1000);
	status = pthread_mutex_unlock(&data->mutex);
	if (status != 0)
		return (-1);
	return (0);
}

int 	get_start_time(t_data *data)
{
	int	status;
	
	status = pthread_mutex_lock(&data->mutex);
	if (status != 0)
		return (-1);
	status = gettimeofday(&data->start_time, NULL);
	if (status == -1)
		return (-1);
	status = pthread_mutex_unlock(&data->mutex);
	if (status != 0)
		return (-1);
	return (0);
}

// il me faut pouvoir check le temps a n'importe quel moment. Il faut que le temps soit compte en ms a partir du debut, a chaques fois qu un philosophe fait une action,
// il faut que je calcul le temps qui s est ecouler.