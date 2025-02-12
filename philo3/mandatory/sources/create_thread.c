/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:15 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/12 18:40:08 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < data->philo[0].nbr_philo)
	{
		printf("je suis le philo numero : %d\n", data->philo[i].id);
		printf("Voici mon temps pour mourrir : %ld\n", data->philo[i].time_to_die);
		printf("Voici mon temps pour dormir : %ld\n", data->philo[i].time_to_sleep);
		printf("Voici mon temps pour manger : %ld\n", data->philo[i].time_to_eat);
		printf("Ma fourchette a ma gauche est la : %d\n", data->philo[i].left_fork->fork_id);
		printf("Ma fourchette a ma droite est la : %d\n", data->philo[i].right_fork->fork_id);
		printf("Je dois manger %d fois \n", data->philo[i].max_meal_nbr);
		printf("Actuellement, j'ai manger %d fois au total\n", data->philo[i].current_meal_nbr);
		printf("Au total, nous sommes %d autour de la table\n", data->philo[i].nbr_philo);
		printf("\n");
	}
	return (0);
}