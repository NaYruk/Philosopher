/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:44:58 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/11 12:46:11 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Function for free all data */

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&data->forks[i].fork);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->forks);
	if (data->philos)
		free(data->philos);
	free(data);
	return ;
}

int	main(int argc, char **argv)
{
	t_data *data;
	
	data = NULL;
	if (argc != 6)
		return (error_nbr_arg());
	if (parse_args(argv) == -1)
		return (-1);
	if (init_data(argv, &data) == -1)
		return (-1);
	if (threads_create(data, data->philos) == -1)
		return (-1);
	free_all(data);
	return (0);
}
