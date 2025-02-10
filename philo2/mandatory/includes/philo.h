/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:25:19 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/02/10 16:59:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Headers for Functions */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/* Struct for fork */

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

/* Struct for each Philosopher */

typedef struct	s_philos
{
	pthread_t	thread_id;
	int			id;
	long		time_last_meal;
	int			counter_of_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
}				t_philos;

/* Struct to bring all the data */

typedef struct	s_data
{
	t_fork		*forks;
	t_philos	*philos;
	long		nbr_philo;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		max_meals_nbr;
	long		start_time_in_ms;
	long		start_time;
	int 		nbr_philo_finish_meat;
}				t_data;

/* Struct for join a Philo and all the data */

typedef struct	s_philo_data
{
	t_philos	*philo;
	t_data		*data;
}				t_philo_data;

/* Definition of each Functions : */

/* Functions error */
int	error_nbr_arg(void);
int	error_args(void);
int	memory_error(void);
int	mutex_error(t_data *data, int nbr_mutex_destroy);
int	thread_error(void);

/* Function for free data */
void	free_all(t_data *data);

/* Function for parse args and detecte any errors */
int	parse_args(char **argv);

/* Function for Initialize data */
int	init_data(char **argv, t_data **data);

/* Function for create all Threads */
int	threads_create(t_data *data);

/* Function called by the Threads */
void	*threads_process(void *arg);

int		get_start_time(t_data *data);
long	get_current_time(t_data *data);

int	try_to_eat(t_philos *philo, t_data *data);
int	take_forks(t_philos *philo, t_data *data);
int	drop_forks(t_philos *philo);

#endif