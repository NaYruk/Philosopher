/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:30:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/14 18:55:37 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Header for Functions */
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define ROUGE	"\033[31m"
# define RESET	"\033[0m"
# define VERT	"\033[32m"

/* 
	Struct for each fork :
	fork 0 = right philo 1
	fork 0 = left philo max
	fork 1 = left philo 1
	fork 1 = right philo 2
*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

/* Struct for each Philosophers she contain all data for each philosophers */
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				dead_or_not;
	int				nbr_philo;
	int				max_meal_nbr;
	int				current_meal_nbr;
	long			start_time;
	long			current_time;
	long			last_meal_time;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*stop_process_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*time_mutex;
}				t_philo;

/* Struct for regroup all data */
typedef struct s_data
{
	int				meals_finished;
	t_fork			*forks;
	t_philo			*philo;
	pthread_t		monitoring_thread;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	time_mutex;
}	t_data;

/* Declaration of Functions */

/* Function for write an error */
int		write_an_error(char *str);

/* Function for check the validity of each arguments */
int		check_args(char **argv);

/* Function for Initialize each Structure */
int		init_all(t_data **data, char **argv);
int		initialize_philos(t_philo **philo, t_data *data, char **argv);

/* Utils Functions */
int		convert_char_to_int(char *str);
int		get_time(long	*time);
void	ft_usleep(long milliseconds, t_philo *philo);

/* Function for free data and mutex */
void	free_forks(t_fork *forks, int nbr_forks);
void	free_data(t_data **data);
void	destroy_mutex(t_data **data);

/* Function for create all threads */
int		create_threads(t_data *data);

/* Function for wait the end of each Threads */
int		wait_threads(t_data *data);

/* Function execute by the monitoring thread ! */
void	*monitoring(void *arg);

/* Function execute by each philosophers thread */
void	*philo_routine(void *arg);

/* Routines Philosophers Functions */
int		try_to_eat(t_philo *philo);

/* Function for write any state message for threads */
int		write_msg(t_philo *philo, char *str);

#endif