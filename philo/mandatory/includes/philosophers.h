/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:35:04 by mmilliot          #+#    #+#             */
/*   Updated: 2025/01/29 20:20:06 by mmilliot         ###   ########.fr       */
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

typedef struct	s_philosophers
{
	int				id;
	int				number_of_meals;
	long			last_meal_time;
	pthread_mutex_t	fork;
	pthread_t		thread;
}	t_philosophers;

typedef struct	s_data
{
	pthread_mutex_t	mutex;
	int				nb_philo;
	int				time_for_die;
	int				time_for_eat;
	int				time_for_sleep;
	int				number_of_meals_for_exit;
	int				nbr_philos_finish_meal;
	struct timeval	start_time;
	struct timeval	current_time;
	long			elapsed_time;			
	t_philosophers	*philos;
}	t_data;

typedef struct	s_thread_data
{
	t_data			*data;
	t_philosophers	*philosophers;
}	t_thread_data;

/* Functions declarations */

int		invalid_arguments(void);
int		invalid_arguments_nbr(t_data *data);
int		creating_thread_error(t_data *data);
void	*error_in_a_thread(t_thread_data *thread_data);
void	*error_with_a_fork(t_thread_data *thread_data);
int		check_and_stocking_args(t_data *data, char **argv);
void	free_all(t_data *data, int destroy_fork);
void	*do_philo_actions(void *thread_data);
int		try_to_eat(t_data *data, t_philosophers *philo);
int		get_current_time(t_data *data);
int		get_start_time(t_data *data);
int		take_forks(t_data *data, t_philosophers *philo);
int		drop_the_fork(t_data *data, t_philosophers *philo);

#endif