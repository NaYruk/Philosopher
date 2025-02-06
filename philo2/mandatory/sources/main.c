/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:44:58 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/06 17:15:49 by mmilliot         ###   ########.fr       */
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
	if (threads_create(data) == -1)
		return (-1);
	free_all(data);
	return (0);
}

//apres avoir parser les arguments, il faut les stocker dans les structures donc les mallocs et tout stocker.
