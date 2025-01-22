/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:35:04 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/22 23:58:33 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* Includes for functions */

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

/* Struct for each Philosophers */

typedef struct	s_data
{
	pthread_mutex_t	mutex;
	int				nb_philo;
	int				time_for_die;
	int				time_for_eat;
	int				time_for_sleep;
	int				number_of_meals_for_exit;
}	t_data;


/* Functions declarations */

int	invalid_arguments(void);
int	invalid_arguments_nbr(t_data *data);
int	check_and_stocking_args(t_data *data, char **argv);

#endif