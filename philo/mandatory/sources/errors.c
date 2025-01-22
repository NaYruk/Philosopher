/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:45:53 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/23 00:00:00 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philosophers.h"

void	free_all(t_data *data)
{
	if (data != NULL)
	{
		pthread_mutex_destroy(&(data->mutex));
		free(data);
	}
	return ;
}

int	invalid_arguments(void)
{
	write(2, "Number of Arguments is invalid\n", 31);
	write(2, "Need 6 Arguments : \n", 20);
	write(2, "./exec nb_philosophers time_to_die time_to_eat ", 47);
	write(2, "time_to_sleep nb_dish_for_exit\n", 32);
	return (1);
}

int	invalid_arguments_nbr(t_data *data)
{
	free_all(data);
	write(2, "A Number is Invalid\n", 20);
	write(2, "Need a positive number !\n", 26);
	return (1);
}