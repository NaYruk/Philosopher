/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_stocking_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:34:09 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/23 00:25:43 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

/* simplify Atoi for verify the validity of each argument */

int 	ft_atoi(char  *str)
{
	int	i;
	int	result;
	
	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/* 
	Funtion for check the validy of each
	arguments and stock the numbers in associate variables 
*/

int	check_and_stocking_args(t_data *data, char **argv)
{
	int	i;
	
	i = 1;
	while (argv[i] != NULL)
	{
		if (i == 1)
			data->nb_philo = ft_atoi(argv[i]);
		else if (i == 2)
			data->time_for_die = ft_atoi(argv[i]);
		else if (i == 3)
			data->time_for_eat = ft_atoi(argv[i]);
		else if (i == 4)
			data->time_for_sleep = ft_atoi(argv[i]);
		else
			data->number_of_meals_for_exit = ft_atoi(argv[i]);
		i++;
	}
	if (data->nb_philo == -1 || data->time_for_die == -1 ||
		data->time_for_eat == -1 || data->time_for_sleep == -1 ||
		data->number_of_meals_for_exit == -1)
		return (-1);
	return (0);
}
